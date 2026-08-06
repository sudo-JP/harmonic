#include <aubio/aubio.h>
#include <sndfile.hh>
#include <chrono>
#include <vector>

namespace harmonic {
    struct TimeInterval {
        std::chrono::duration<double> start;
        std::chrono::duration<double> end;
    };

    typedef TimeInterval BeatSegment;

    class AudioAnalyzer {
        public:
        AudioAnalyzer(SndfileHandle audio_file, TimeInterval timestamp);
        std::vector<BeatSegment> extract_beats();

        private:
        SndfileHandle m_audio_file; 
        TimeInterval m_timestamp; 
        std::unique_ptr<aubio_tempo_t, decltype(&del_aubio_tempo)> m_tempo{nullptr, del_aubio_tempo}; 
    };  
}
