#pragma once

#include "lizard/tester.hpp"

TEST(sample_tester) {

    // onstart("A label for it", []() {
    //     std::cout << std::endl << "BEFORE ANY SPEC GOT STARTED!" << std::endl;
    // });

    // onterminate("A label for it", []() {
    //     std::cout << std::endl << "AFETR ALL SPECs GOT FINISHED!" << std::endl;
    // });

    // prespec("A label for it", [](auto name) {
    //     std::cout << std::endl << "STARTING SPEC: " << name << std::endl;
    // });

    // postspec("A label for it", [](auto name) {
    //     std::cout << std::endl << "FINISHED SPEC: " << name << std::endl;
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
