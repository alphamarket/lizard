C++ Tester
---

A lightweight and efficient C++ testing package.

How to step up? ( 1 Step )
-----
Assume you have project named `cppApp` written in C++.


<h5>Step# 1: Clone the repo.</h5>
<hr />
Clone current C++ Tester repository into your project as [submodule](http://git-scm.com/docs/git-submodule).

```BASH
cd "/path/to/cppApp"
# Now we are under your project's subdirectory.
git submodule add "https://github.com/dariushha/cpptester.git" test
# Move into test folder
cd "test"
# Delete the submodule's origin repo. address
git remote remove origin
# Set your testing remote repo.
git remote add origin "https://some-url.com/someusr/somerepo.git"
# That is it.
```

How to use it? ( 3 Steps )
---
It's really easy. All you need is to write your test class `anywhere you like`(I personally suggest you create them under `test/TestCases` for your project integrity). and address it in `test/manifest.hpp` and then compile/run the `test/testerMain.cpp`. That is all.


<h5>Step# 1: Write your test class</h5>
<hr />
For convenience there are multiple macros [defined](https://github.com/dariushha/cpptester/wiki/List-of-assertion-macros) for [assertions](http://www.cplusplus.com/reference/cassert/assert). as the [demo](https://github.com/dariushha/cpptester-demo) of C++ Tester assume we have a class named <u>[line](https://github.com/dariushha/cpptester-demo/blob/master/hpp/line.hpp)</u> and we wrote following `Test` class:


```CPP
/*
 * This file construct test units for testing
 * TargetFile: https://github.com/dariushha/cpptester-demo/blob/master/hpp/line.hpp
 *
 * File:   lineTestCase.hpp
 * Author: dariush
 *
 * Created on March 30, 2014, 12:37 AM
 */
#define __LINE_TEST__
#ifdef __LINE_TEST__
/**
 * The general abstract testCass
 */
#include "../../hpp/testCase.hpp"
/**
 * The class we want to test
 */
#include "../../../hpp/line.hpp"
/**
 * Any other dependency includes here 
 */
using namespace demo;
using namespace CPP_TESTER;
/**
 * These name spaces are optional
 */
namespace CPP_TESTER { namespace TESTS {
    /**
     * The test class, which inherit from `CPP_TESTER::testCase`
     */
    class lineTestCase : public testCase {
    /**
     * Our test case's API
     */
    public:
        /**
         * Init your test class here.
         */
        bool __init() { }
        /**
         * Free any resources used by your class here.
         */
        bool __dispose() { }
        /**
         * Run your tests here
         */
        bool __run(int argc = 0, void** argv = NULL) {
            /**
             * You can do any test here
             */
            // I did this!!
            BESURE(this->heap_check());
        }
    private:
        /**
         * Creates an instance on heap and tests its behaviours.
         */
        bool heap_check() {
            // a instance created
            line* __line = new line(0, "TEST_LINE");
            // for demo: check created instance is a pointer?
            IS_POINTER(__line);
            // at instance's ctor we initialized the line# to 0
            // It should be as passed 
            IS_ZERO(__line->getLineNumber());
            // The line's content should be as passed
            IS_EQUAL(__line->getContent(), "TEST_LINE");
            // No source defined, so source should be NULL
            IS_NULL(__line->getSource());
            delete(__line);
            // create a new line 
            __line = new line(-1, "INVALID_TEST_LINE");
            // since the line# is `size_t` so any negative line#
            // will dealt as unsigned.
            IS_NOT(__inv_line.getLineNumber(), -1);
            // test line content
            IS_EQUAL(__line->getContent(), "INVALID_TEST_LINE");
            // no source defined as well
            IS_NULL(__line->getSource());
            delete(__line);
__ASSERT_SUCCESS:
            return true;
__ASSERT_FAILURE:
            return false;
        }
    };
} }
#endif
```
> <b>How it woks?</b>

Easy! in `test/testerMain.cpp` the main function will call first `__init()` which you will initialize your test class and then `__run(int argc = 0, void** argv = NULL)` with any argument <b>you</b> have provided in `test/manifest.hpp` which you have the opportunity to test you class with anything in `__run()` function and after you have done with your test(i.e `__run()`) it will call the `__dispose()` function.

> <b>Note:</b> Every each test class you write <b>MUST</b> inherit from  `CPP_TESTER::testCase` 
