#include "tester.hpp"

void lizard::Tester::Base::flush_buffer() const {
    change_stdout(false);
    std::string output = stdout_buffer.str();
    if(output.length() != 0)
        std::cout << output << std::flush;
    clear_buffer();
}

void lizard::Tester::Base::clear_buffer(void) const {
    stdout_buffer.clear();
    stdout_buffer.str(std::string(""));
}

void lizard::Tester::Base::change_stdout(bool change2buffer) const {
    if(change2buffer) {
        clear_buffer();
        std::cout.rdbuf( stdout_buffer.rdbuf() );
    } else {
        std::cout.rdbuf( stdout_handler );
    }
}


lizard::Tester::TestUnitResult
lizard::Tester::Base::run() const {
    size_t counter = 0;
    TestUnitResult output_result;
    const auto handle_output = [&](const size_t& offest = 4) {
        auto output = buffer();
        std::string out = "";
        for(auto iter = output.begin(); iter != output.end(); iter++) {
            out.push_back(*iter);
            if(*iter == '\n')
                out += std::string(offest, ' ');
        }
        if(!output.empty()) {
            // right trim the output
            while(out.back() == '\n' || out.back() == ' ' || out.back() == '\t')
                out.pop_back();
            // print the output
            std::cout << std::string(offest, ' ') << out << std::endl << std::flush;
        }
    };
    const auto print_success = []() {
        printf("  " COLORIFY(MKCOLOR("48;5;22") MKCOLOR("38;5;15"),  "[ PASSED ]") " ");
    };
    const auto print_failed = []() {
        printf("  " COLORIFY(MKCOLOR("48;5;1") MKCOLOR("38;5;15"),   "[ FAILED ]") " ");
    };
    const auto print_skipped = []() {
        printf("  " COLORIFY(MKCOLOR("48;5;166") MKCOLOR("38;5;15"), "[  SKIP  ]") " ");
    };
    const auto call_onstarts = [&]() {
        for(const auto& callback : _executioners.at("onstarts"))
            callback.second();
    };
    const auto call_prespecs = [&](const auto& spec) {
        for(const auto& callback : _conditioners.at("prespecs"))
            callback.second(spec.first);
    };
    const auto call_postspecs = [&](const auto& spec) {
        for(const auto& callback : _conditioners.at("postspecs"))
            callback.second(spec.first);
    };
    const auto call_onterminates = [&]() {
        for(const auto& callback : _executioners.at("onternimates"))
            callback.second();
    };
    printf(COLORIFY(MKCOLOR("1"), "%s") "\n", name().c_str());
    enum RESULT { PASSED, FAILED, SKIPPED };
    try {
        call_onstarts();
        for(const auto& spec : _executioners.at("specs")) {
            RESULT result = PASSED;
            const auto line = "%0" + std::to_string(std::to_string(_executioners.at("specs").size()).length()) + std::string("zu/%zu Test: `" COLORIFY(MKCOLOR("1"), "%s") "`");
            printf(("%s" + line).c_str(), COLORIFY(MKCOLOR("5"), "  [  ....  ] "), ++counter, _executioners.at("specs").size(), spec.first.c_str());
            fflush(stdout);
            change_stdout(true);
            auto start = std::chrono::high_resolution_clock::now(),
                 end = start;
            bool error_on_postback = false;
            try {
                call_prespecs(spec);
                spec.second();
                try { call_postspecs(spec); } catch(...) { error_on_postback = true; }
                end = std::chrono::high_resolution_clock::now();
                output_result.number_of_success += 1;
            } catch(const lizard::LizardTestSkipError& e) {
                if(!error_on_postback)
                    try { call_postspecs(spec); } catch(...) { }
                result = SKIPPED;
                output_result.number_of_skips += 1;
                end = std::chrono::high_resolution_clock::now();
                if(strlen(e.what())) {
                    std::cout << std::string(80, '-') + "\n"
                              COLORIFY(MKCOLOR("1"), "Location: ") + e.file() + ":" + std::to_string(e.line()) + "\n"
                              COLORIFY(MKCOLOR("1"), "Message: ") + std::string(e.what()) + "\n" +
                              std::string(80, '-') + "\n";
                }
            } catch(const lizard::LizardTestFailError& e) {
                if(!error_on_postback)
                    try { call_postspecs(spec); } catch(...) { }
                result = FAILED;
                output_result.number_of_errors += 1;
                end = std::chrono::high_resolution_clock::now();
                if(strlen(e.what())) {
                    std::cout << std::string(80, '-') + "\n"
                              COLORIFY(MKCOLOR("1"), "Location: ") + e.file() + ":" + std::to_string(e.line()) + "\n"
                              COLORIFY(MKCOLOR("1"), "Message: ") + std::string(e.what()) + "\n" +
                              std::string(80, '-') + "\n";
                }
            } catch(const std::exception& e) {
                if(!error_on_postback)
                    try { call_postspecs(spec); } catch(...) { }
                result = FAILED;
                std::string message = e.what();
                output_result.number_of_errors += 1;
                end = std::chrono::high_resolution_clock::now();
                if(message.empty())
                    message = "You have an uncaught error!";
                std::cout << std::string(80, '-') + "\n"
                          COLORIFY(MKCOLOR("48;5;1") MKCOLOR("38;5;15"),   "[ UNCAUGHT EXCEPTION ]") "\n" +
                          COLORIFY(MKCOLOR("1"), "Message: ") + message + "\n" +
                          std::string(80, '-') + "\n";
            }
            change_stdout(false);
            printf("\r");
            if(result == PASSED)
                print_success();
            else if(result == FAILED)
                print_failed();
            else if(result == SKIPPED)
                print_skipped();
            printf(line.c_str(), counter, _executioners.at("specs").size(), spec.first.c_str());
            printf(COLORIFY(MKCOLOR("37"), " - %.4f") " sec.\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1e+6);
            handle_output();
        }
        call_onterminates();
    } catch(const lizard::LizardTestSkipError& e) {
        change_stdout(true);
        output_result.number_of_skips += 1;
        std::string message = e.what();
        if(message.empty())
            message = "You have skipped something in onstart / onterminate callbacks!";
        std::cout << std::string(80, '-') + "\n"
                  COLORIFY(MKCOLOR("48;5;166") MKCOLOR("38;5;15"),   "[ ATTENTION ]") "\n" +
                  COLORIFY(MKCOLOR("1"), "Location: ") + e.file() + ":" + std::to_string(e.line()) + "\n"
                  COLORIFY(MKCOLOR("1"), "Message: ") + message + "\n" +
                  std::string(80, '-') + "\n";
        change_stdout(false);
        handle_output();
    } catch(const lizard::LizardTestFailError& e) {
        change_stdout(true);
        output_result.number_of_errors += 1;
        std::string message = e.what();
        if(message.empty())
            message = "You have an error in onstart / onterminate callbacks!";
        std::cout << std::string(80, '-') + "\n"
                  COLORIFY(MKCOLOR("48;5;1") MKCOLOR("38;5;15"),   "[ ATTENTION ]") "\n" +
                  COLORIFY(MKCOLOR("1"), "Location: ") + e.file() + ":" + std::to_string(e.line()) + "\n"
                  COLORIFY(MKCOLOR("1"), "Message: ") + message + "\n" +
                  std::string(80, '-') + "\n";
        change_stdout(false);
        handle_output();
    } catch(const std::exception& e) {
        change_stdout(true);
        output_result.number_of_errors += 1;
        std::string message = e.what();
        if(message.empty())
            message = "You have an uncaught error in onstart / onterminate callbacks!";
        std::cout << std::string(80, '-') + "\n"
                  COLORIFY(MKCOLOR("48;5;1") MKCOLOR("38;5;15"),   "[ UNCAUGHT EXCEPTION ]") "\n" +
                  COLORIFY(MKCOLOR("1"), "Message: ") + message + "\n" +
                  std::string(80, '-') + "\n";
        change_stdout(false);
        handle_output();
    }
    return output_result;
}

lizard::Tester::TestUnitResult
lizard::Tester::run() const {
    TestUnitResult output;
    for(const auto& tester : _test_units) {
        auto result = tester->run();
        output.number_of_skips += result.number_of_skips;
        output.number_of_errors += result.number_of_errors;
        output.number_of_success += result.number_of_success;
        printf("\n");
        fflush(stdout);
    }
    return output;
}
