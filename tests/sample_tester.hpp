#pragma once

#include <iostream>
#include "lizard/lizard.hpp"

TESTER(sample_tester,

    // onbefore([]() {
    //     std::cout << std::endl << "BEFORE ANY SPEC GOT STARTED!" << std::endl;
    // });

    // onafter([]() {
    //     std::cout << std::endl << "AFETR ALL SPECs GOT FINISHED!" << std::endl;
    // });

    // onskip([](auto name, auto err) {
    //     std::cout << std::endl << "SKIPPED: " << name << " WITH MESSAGE: " << err.what() << std::endl;
    // });

    // onfail([](auto name, auto err) {
    //     std::cout << std::endl << "FAILED: " << name << " WITH MESSAGE: " << err.what() << std::endl;
    // });

    // onprespec([](auto name) {
    //     std::cout << std::endl << "STARTING SPEC: " << name << std::endl;
    // });

    // onpostspec([](auto name) {
    //     std::cout << std::endl << "FINISHED SPEC: " << name << std::endl;
    // });

    spec(sum, []() {
        IS_EQUAL(1 + 2, 3);
    });
    
    spec(multiply, []() {
        SKIP_WITH_MESSAGE("SKIP WITH MESSAGE");
    });
    
    spec(minus, []() {
        IS_EQUAL(1 - 2, -1);
    });

    spec(faulty, []() {
        IS_EQUAL(2 / 2, -1);
    });

    spec(divide, []() {
        IS_EQUAL(2 / 2, 1);
    });
)