C++ Tester
===

A lightweight and efficient C++ testing package.

Topics
---
* [Prerequisites](#prerequisites)
* [How to step up?](#how-to-use-it--3-steps-) ( 1 Step )
* [How to use it?](#how-to-use-it--3-steps-) ( 3 Steps )
* [Demo](#demo)

Prerequisites
---
No prerequisites is needed. The project is as is.
This project has been compiled and tested with `g++-4.6.real (Ubuntu/Linaro 4.6.4-1ubuntu1~12.04) 4.6.4` with 100% success.

> There is NO WARRANTY if it works with other COMPILERS or on other OPERATING SYSTEMS. 

How to step up? ( 1 Step )
-----
Assume you have project named `cppApp` written in C++.

<hr />
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

<hr />
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
            NOT_EQUAL(__line->getLineNumber(), (unsigned)-1);
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

> <b>Note:</b> Every each test class you write <b>MUST</b> inherit from  `CPP_TESTER::testCase`. 

<hr />
<h5>Step# 2: Add your class into manifest list</h5>
<hr />
After you have wrote your test you need to introduce your test class to C++ Tester, so you need to add some few lines in `test/manifest.hpp` file. The few things you need to add into `test/manifest.hpp` file is as follow:
    * `#include` your test file.
    * Add a `test_case`.
        * Should have name(For display purposes in our example e.g `Line Tester`).
        * Should have a `test_pack`.(For involing purposes)
            * Should have an instance of your test class.
            * Any optional argument your may want to pass as `test_args`.


So based on above details the `test_case` instance for our `lineTestCase` looks like as bellow:

```CPP
    test_case
    (
        // any optional name
        "Line Tester",
        test_pack
        (
            // The instance of your test class
            new CPP_TESTER::TESTS::lineTestCase(),
            // in this case we will pass empty argument to our test class
            test_args()
        )
    )
```

In `test/manifest.hpp` there is a `test_case _tests[]`. You need to add the above `test_case` into `_tests[]` to make your test class available for testing. See [this](https://github.com/dariushha/cpptester-demo/blob/master/test/manifest.hpp) for more detail about `test/manifest.hpp`.  


<hr />
<h5>Step# 3: You are DONE!</h5>
<hr />
Just all you need is compile your `test/testerMain.cpp` file and execute it to see your test results!

Demo
---
For demo download/clone and compiler-execute [this](https://github.com/dariushha/cpptester-demo).
