/*
 * File:   manifest.hpp
 * Author: dariush
 *
 * Created on April 1, 2014, 2:13 AM
 */
#ifndef MANIFEST_HPP
#define	MANIFEST_HPP
#include "hpp/testCase.hpp"
#include <vector>
/*
 * Include test case files
 */
//#include "TestCases/example/fooTestCase.hpp"
//#include "TestCases/example/barTestCase.hpp" 
namespace CPP_TESTER {
    typedef vector< void* > test_args;
    typedef pair< testCase*,  test_args > test_pack;
    typedef pair< std::string, test_pack > test_case;
    typedef vector<test_case> test_suite;
    /**
     * Builds test suite for testing
     * @return The test_cases
     */
    test_suite BuildTestSuite() {
        test_case _tests[] = {
            /*
            test_case
            (
                    "Foo Tester",
                    test_pack
                    (
                        new fooTestCase(),
                        test_args()
                    )
            ),
            test_case
            (
                    "Bar Tester",
                    test_pack
                    (
                        new barTestCase(),
                        test_args()
                    )
            )*/
        };
        return test_suite(_tests, _tests + sizeof(_tests) / sizeof(test_case));
    }
}
#endif	/* MANIFEST_HPP */
