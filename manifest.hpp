#ifndef MANIFEST_HPP
#define MANIFEST_HPP

#include "lizard/lizard.hpp"

// include test case files
#include "tests/sample_tester.hpp"


MANIFEST({
    /*
    * use following macros to register test cases
    *      $(<test label>, <test class name>);
    *      lizard_register(<test class name>);
    *      lizard_register_custom(<test label>, <test class name>);
    *
    * example:
    *      $("[DEBUGS]", test::debug_tester);
    *      $("/Helpers", test::helpers_tester);
    *      lizard_register(test::template_tester);
    */
    $("Sample Tester", lizard::test::sample_tester);
})

#endif  /* MANIFEST_HPP */
