#include "../manifest.hpp"

namespace lizard {
    // init test indexer/counter
    size_t lizard_test_errors = 0;
    size_t lizard_test_counter = 0;
    size_t lizard_test_warnings = 0;
    // make a new out stream
    std::ostringstream lizard_std_buffer;
    // make a backup from current stdout
    std::streambuf* const lizard_stdout = std::cout.rdbuf();
    // global accessable current testcase
    test_case* lizard_test_case = NULL;
    /**
     * @brief at exit handler
     */
    void lizard_atExit(void);
    /**
     * @brief flush buffer outputs to origin stdout
     */
    void lizard_flush_buffer(bool success = true, bool warning = false);
    /**
     * @brief clearouts stdbuffer
     */
    void lizard_clear_buffer(void);
    /**
     * @brief redirect the stdout
     * @param change2buffer if it is true then the stdout will be redirected to
     *  buffer, otherwise it will restored to origin stdout stream line.
     */
    void lizard_change_stdout(bool change2buffer = false);

    void lizard_atExit(void) {
        extern size_t lizard_test_counter;
        lizard_change_stdout(false);
        const size_t lizard_test_successes = lizard_test_counter - lizard_test_errors - lizard_test_warnings;
        std::cout << std::endl << "Total `" << lizard_test_counter << "` tests have been carried out!" << std::endl;
        if(lizard_test_successes == lizard_test_counter)
            std::cout << COLORIFY(MKCOLOR(42) + MKCOLOR(30), "[All of Them Succeed!]") << std::endl;
        else {
            std::cout << COLORIFY(MKCOLOR(41), "Errors   : " << lizard_test_errors << std::string(6 - std::to_string(lizard_test_errors).size(), ' ')) << std::endl
                      << COLORIFY(MKCOLOR(43) + MKCOLOR(30), "Warnings : " << lizard_test_warnings << std::string(6 - std::to_string(lizard_test_warnings).size(), ' ')) << std::endl
                      << COLORIFY(MKCOLOR(42) + MKCOLOR(30), "Successes: " << lizard_test_successes << std::string(6 - std::to_string(lizard_test_successes).size(), ' ')) << std::endl;
        }
        std::cout << std::flush;
    }

    void lizard_flush_buffer(bool success, bool warning) {
        extern test_case* lizard_test_case;
        extern std::ostringstream lizard_std_buffer;
        lizard_change_stdout(false);
        std::string __output = lizard_std_buffer.str();
        if(lizard_test_case != NULL) {
            if(success) {
                std::cout << COLORIFY(MKCOLOR(42) + MKCOLOR(30), "\r[\u221A] ") << COLORIFY(MKCOLOR(42) + MKCOLOR(30), lizard_test_case->first) << std::string(10, ' ') << std::endl << std::flush;
            } else {
                if(!warning)
                    std::cout << COLORIFY(MKCOLOR(41), "\r[X] ") << COLORIFY(MKCOLOR(41), lizard_test_case->first) << std::string(10, ' ') << std::endl << std::flush;
                else
                    std::cout << COLORIFY(MKCOLOR(43), "\r[-] ") << COLORIFY(MKCOLOR(43), lizard_test_case->first) << std::string(10, ' ') << std::endl << std::flush;
            }
        }
        if(__output.length() != 0)
            std::cout << __output << std::flush;
        lizard_clear_buffer();
    }

    void lizard_clear_buffer(void) {
        extern std::ostringstream lizard_std_buffer;
        lizard_std_buffer.clear();
        lizard_std_buffer.str(std::string(""));
    }

    void lizard_change_stdout(bool change2buffer) {
        extern std::ostringstream lizard_std_buffer;
        if(change2buffer) {
            lizard_clear_buffer();
            std::cout.rdbuf( lizard_std_buffer.rdbuf() );
        } else {
            std::cout.rdbuf( lizard_stdout );
        }
    }
}
#if defined(TESTING) && TESTING
/**
 * @brief the main entery point of test project
 */
int main(int, char**) {
    using namespace lizard;
    atexit(&lizard_atExit);
    lizard_manifest();
    for(; lizard_test_counter < lizard_registery::size(); lizard_test_counter++)
    {
        lizard_test_case = lizard_registery::at(lizard_test_counter);
        if(lizard_test_counter != 0)
            std::cout << std::endl;
        std::cout << COLORIFY(MKCOLOR(43) + MKCOLOR(34) + MKCOLOR(5), "[...] " << lizard_test_case->first) << std::flush;
        lizard_change_stdout(true);
        {
            try {
                lizard_test_case->second->run();
                delete lizard_test_case->second;
            } catch(lizard::TestFailException& e) {
                std::cout
                    << "    File: " << e.file() << ":" << e.line() << std::endl
                    << "    Message: " << e.what() << std::endl << std::flush;
                lizard_change_stdout(false);
                lizard_flush_buffer(false);
                lizard_test_errors += 1;
                continue;
            } catch(lizard::TestSkipException& e) {
                lizard_change_stdout(false);
                lizard_flush_buffer(false, true);
                lizard_test_warnings += 1;
                continue;
            }
        }
        lizard_change_stdout(false);
        lizard_flush_buffer();
    }
    lizard_registery::close();
    if(lizard_test_errors)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
#endif

