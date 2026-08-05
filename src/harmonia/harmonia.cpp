#include "harmonia.hpp"
#include <expected>
#include <sndfile.hh>
#include <ranges>

namespace harmonic {
    std::expected<std::monostate, std::string> 
        Harmonia::synthesize(
            std::string input_file, 
            std::string output_file, 
            FunctionInput function_input, 
            TimeInterval timestamp) 
        {
        int domain_min = function_input.domain.min_val; 
        int domain_max = function_input.domain.max_val;
        
        SndfileHandle wav_file(input_file);

        if (domain_min > domain_max) {
            return std::unexpected<std::string>("Invalid domain, min has to be smaller than max");
        } else if (timestamp.end < timestamp.start) {
            return std::unexpected<std::string>("Start must be after end");
        } else if (!wav_file) {
            return std::unexpected<std::string>("Unable to parse .wav file");
        }    

        // Retrieve the pattern produce by func 
        auto vec_func_out = std::views::iota(domain_min, domain_max)
            | std::views::transform([&](int x) { return function_input.f(x); })
            | std::ranges::to<std::vector<int>>();

        return std::monostate();
    }
}

