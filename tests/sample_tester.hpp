#pragma once

#include "lizard/tester.hpp"

TEST(sample_tester) {
    // (v3.0.1)
    // label-less `onstart` can only be defined once!
    // onstart([]() {
    //     std::cout << std::endl << "BEFORE ANY SPEC GOT STARTED!" << std::endl;
    // });

    // (v3.0.1)
    // label-less `onterminate` can only be defined once!
    // onterminate([]() {
    //     std::cout << std::endl << "AFETR ALL SPECs GOT FINISHED!" << std::endl;
    // });

    // (v3.0.1)
    // label-less `prespec` can only be defined once!
    // prespec([](auto name) {
    //     std::cout << std::endl << "STARTING SPEC: " << name << std::endl;
    // });

    // (v3.0.1)
    // label-less `postspec` can only be defined once!
    // postspec([](auto name) {
    //     std::cout << std::endl << "FINISHED SPEC: " << name << std::endl;
    // });

    // onstart("A label for it", []() {
    //     std::cout << std::endl << "BEFORE ANY SPEC GOT STARTED!" << std::endl;
    // });

    spec("sum", []() {
        IS_EQUAL(1 + 2, 3);
    });

    spec("multiply", []() {
        SKIP_WITH_MESSAGE("SKIP WITH MESSAGE");
    });

    spec("minus", []() {
        IS_EQUAL(1 - 2, -1);
    });

    spec("faulty", []() {
        IS_EQUAL(2 / 2, -1);
    });

    spec("divide", []() {
        IS_EQUAL(2 / 2, 1);
    });
}
