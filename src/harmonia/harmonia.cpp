#include "harmonia.hpp"
#include <expected>
#include <sndfile.hh>

namespace harmonic {
    expected<void, string> Harmonia::synthesize(string input_file, string output_file, FunctionInput function_input, TimeInterval timestamp) {
        int domain_min = function_input.domain.min_val; 
        int domain_max = function_input.domain.max_val;
        
        SndfileHandle wav_file(input_file);

        if (domain_min > domain_max) {
            return unexpected<string>("Invalid domain, min has to be smaller than max");
        } else if (timestamp.end > timestamp.start) {
            return unexpected<string>("Start must be after end");
        } else if (!wav_file) {
            return unexpected<string>("Unable to parse .wav file");
        }    
        for (int i = domain_min; i < domain_max; i++) {

        }
    }
}

