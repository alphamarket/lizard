/*
 * File:   manifest.hpp
 * Author: dariush
 *
 * Created on April 1, 2014, 2:13 AM
 */
#ifndef MANIFEST_HPP
#define	MANIFEST_HPP
#include "hpp/registery.hpp"
/*
 * Include test case files
 */
// #include "TestCases/example/fooTestCase.hpp"
namespace CPP_TESTER {
    /**
     * bootstrap the test suite for testing
     */
    void __bootstrap() {
        /* example */
        // registery::__register("Example Tester", new fooTestCase());
    }
}
#endif	/* MANIFEST_HPP */
