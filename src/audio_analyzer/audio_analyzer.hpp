#include <aubio/aubio.h>
#include <sndfile.hh>
#include <chrono>

namespace harmonic {
    struct TimeInterval {
        std::chrono::duration<double> start;
        std::chrono::duration<double> end;
    };

    class AudioAnalyzer {
        public:
        AudioAnalyzer(SndfileHandle audio_file, TimeInterval timestamp);

        private:
        SndfileHandle m_audio_file; 
        TimeInterval m_timestamp; 
        std::unique_ptr<aubio_tempo_t> m_tempo; 
    };  
}
