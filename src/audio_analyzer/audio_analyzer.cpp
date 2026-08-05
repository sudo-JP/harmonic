#include "audio_analyzer.hpp"

namespace harmonic {

    AudioAnalyzer::AudioAnalyzer(SndfileHandle audio_file, TimeInterval timestamp) : 
        m_audio_file(audio_file), m_timestamp(timestamp) {
        m_tempo = nullptr; 
    }
}
