#include "tester.hpp"
#include "../manifest.hpp"

#if defined(TESTING) && TESTING
/**
 * @brief the main entery point of test project
 */
int main(int, char**) {
    using namespace lizard;
    // create a tester object
    Tester tester;
    // ask manifester to execute on the tester
    Manifester().exec(tester);
    // run the tester and fetch the results
    auto result = tester.run();
    // if there were any skips or failures
    if(result.number_of_errors + result.number_of_skips) {
        if(result.number_of_errors)
            std::cout << COLORIFY(MKCOLOR("48;5;1") MKCOLOR("38;5;15"), "[ Oops, be careful! ]") << std::endl;
        else if(result.number_of_skips)
            std::cout << COLORIFY(MKCOLOR("48;5;166") MKCOLOR("38;5;15"), "[ You have skipped something! ]") << std::endl;
        // return with failure as well
        return EXIT_FAILURE;
    }
    std::cout << COLORIFY(MKCOLOR("48;5;22") MKCOLOR("38;5;15"), "[ Everything is OK! ]") << std::endl;
    // otherwise return success
    return EXIT_SUCCESS;
}
#endif
