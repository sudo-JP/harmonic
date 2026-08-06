#include "audio_analyzer.hpp"
#include <algorithm>
#include <aubio/fvec.h>
#include <aubio/tempo/tempo.h>
#include <sndfile.h>
#include <vector>

#define AUBIO_BUF_SIZE 512
#define AUBIO_HOP_SIZE 256

namespace harmonic {
    AudioAnalyzer::AudioAnalyzer(SndfileHandle audio_file, TimeInterval timestamp) : 
        m_audio_file(audio_file), m_timestamp(timestamp) {
        m_tempo.reset(new_aubio_tempo("default", AUBIO_BUF_SIZE, AUBIO_HOP_SIZE, audio_file.samplerate()));
    }

    std::vector<BeatSegment> AudioAnalyzer::extract_beats() {
        std::unique_ptr<fvec_t, decltype(&del_fvec)> ibuf{nullptr, del_fvec}; 
        ibuf.reset(new_fvec(AUBIO_HOP_SIZE));

        std::unique_ptr<fvec_t, decltype(&del_fvec)> tempo_out{nullptr, del_fvec}; 
        tempo_out.reset(new_fvec(1));

        std::vector<BeatSegment> beats; 

        size_t frames = m_audio_file.frames();
        int channels = m_audio_file.channels();
        std::vector<float> temp_buffer(AUBIO_HOP_SIZE * channels); 
        smpl_t prev_timestamp = 0; 

        for (size_t i = 0; i < frames; i += AUBIO_HOP_SIZE) {
            // for ex: channel 1 has [mono, mono, ..]
            // for channel 2 has [left, right, ..], aka stereo
            // just avg the channels into temp buffer 
            uint_t buffer_read = m_audio_file.readf(temp_buffer.data(), AUBIO_HOP_SIZE);
            buffer_read = std::min(buffer_read, ibuf->length);

            // PERF: Oh hey, a sharded problem that can be solved with 
            // optimization threading
            for (size_t j = 0; j < buffer_read; j++) {
                float sum = 0; 
                for (size_t z = j * channels; z < (j + 1) * channels; z++) {
                    sum += temp_buffer[z]; 
                }
                ibuf->data[j] = sum / channels;
            }
            aubio_tempo_do(m_tempo.get(), ibuf.get(), tempo_out.get());

            smpl_t is_beat = fvec_get_sample(tempo_out.get(), 0);
            if (is_beat > 0) {
                // Beat detected 
                smpl_t last_timestamp = aubio_tempo_get_last_s(m_tempo.get());

                std::chrono::duration<double> start_timestamp(prev_timestamp);
                std::chrono::duration<double> end_timestamp(last_timestamp);
                beats.push_back(BeatSegment {
                    .start = start_timestamp, 
                    .end = end_timestamp,
                });

                prev_timestamp = last_timestamp;
            }
        }
        return beats;
    }
}
