#ifndef SAMPLE_TESTER_HPP
#define SAMPLE_TESTER_HPP

#include "lizard/lizard.hpp"

TESTER(sample_tester,
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

#endif
