#include <expected>
#include <functional>
#include <string>
#include <chrono>

namespace harmonic {
    using namespace std;
    struct IntegerInterval {
        int min_val;
        int max_val;
    };

    struct FunctionInput {
        function<int(int)> f;
        IntegerInterval domain; 
    };

    struct TimeInterval {
        chrono::duration<double> start;
        chrono::duration<double> end;
    };

    class Harmonia {
    public:
        expected<void, string> synthesize(string input_file, string output_file, FunctionInput function_input, TimeInterval timestamp);
    private:
    };
}

