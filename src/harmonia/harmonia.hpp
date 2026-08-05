#include <expected>
#include <functional>
#include <string>
#include <variant>
#include "../audio_analyzer/audio_analyzer.hpp"

namespace harmonic {
    struct IntegerInterval {
        int min_val;
        int max_val;
    };

    struct FunctionInput {
        std::function<int(int)> f;
        IntegerInterval domain; 
    };


    class Harmonia {
    public:
        std::expected<std::monostate, std::string> synthesize(
            std::string input_file, 
            std::string output_file, 
            FunctionInput function_input, 
            TimeInterval timestamp
        );
    private:
    };
}

