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
There is a [setup script](https://github.com/noise2/cpptester/blob/master/cpptester-setup) provided to make cloning this C++ Tester repository into your project easier

```BASH
cd "/path/to/cppApp"
# adds this repo into your project as a submodule and clears development history of this repo. too 
curl https://raw.githubusercontent.com/noise2/cpptester/master/cpptester-setup | bash
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
 * TargetFile: https://github.com/dariushha/cpptester-demo/blob/master/src/line.hpp
 *
 * File:   lineTestCase.hpp
 * Author: dariush
 */
#ifndef LINETESTCASE_HPP
#define LINETESTCASE_HPP
/**
 * The class we want to test
 */
#include "../../src/line.hpp"
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
         * @brief Runs before the run()
         */
        virtual void pre_run()  { }
        /**
         * @brief Runs after the run()
         */
        virtual void post_run() { }
        /**
         * @brief Runs the testcase
         */
        void run(size_t, void**) {
            /**
             * You can do any test here
             */
            BESURE(this->alloc_check());
        }
    private:
        /**
         * Creates an instance on heap and tests its behaviours.
         */
        bool alloc_check() {
            // a instance created
            line* line_ = new line(0, "TEST_LINE");
            // for demo: check created instance is a pointer?
            IS_POINTER(line_);
            // at instance's ctor we initialized the line# to 0
            // It should be as passed
            IS_ZERO(line_->getLineNumber());
            // The line's content should be as passed
            IS_EQUAL(line_->getContent(), "TEST_LINE");
            // No source defined, so source should be NULL
            IS_NULL(line_->getSource());
            delete(line_);
            // create a new line
            line_ = new line(-1, "INVALID_TEST_LINE");
            // since the line# is `size_t` so any negative line#
            // will dealt as unsigned.
            NOT_EQUAL(line_->getLineNumber(), (unsigned)-1);
            // test line content
            IS_EQUAL(line_->getContent(), "INVALID_TEST_LINE");
            // no source defined as well
            IS_NULL(line_->getSource());
            delete(line_);
            return true;
        }
    };
} }
#endif // LINETESTCASE_HPP
```
> <b>Note:</b> Every each test class you write <b>MUST</b> inherit from  `CPP_TESTER::testCase`. 

<hr />
<h5>Step# 2: Add your class into manifest list</h5>
<hr />
After you have wrote your test you need to introduce your test class to C++ Tester, so you need to add some few lines in `test/manifest.hpp` file in order to register your test cases.

The blow code is an example of you register your test cases:

```CPP
#ifndef MANIFEST_HPP
#define	MANIFEST_HPP
#include "hpp/teststrap.hpp"
#include "hpp/registery.hpp"
/*
 * Include test case files
 */
#include "TestCases/lineTestCase.hpp"
namespace CPP_TESTER {
    /**
     * bootstrap the test suite for testing
     */
    void __bootstrap() {
        /* register the line tester */
        registery::__register("Line Tester", new CPP_TESTER::TESTS::lineTestCase);
        // OR if you wish to pass some argument
        // registery::__register("Line Tester", new CPP_TESTER::TESTS::lineTestCase, 
        //                          { new someInstance(), new string("Hello World!") });

    }
}
#endif	/* MANIFEST_HPP */
```
> <small>The above code snap was taken from [C++ Tester's Demo](https://github.com/dariushha/cpptester-demo).</small>

All you need to do is `register` your test case in `__bootstrap()` function in `test/manifest.hpp` file.

> <b>Note: </b>The test cases will execute in order they have been registered!

<hr />
<h5>Step# 3: You are DONE!</h5>
<hr />
Just all you need to do is compile your `test/testerMain.cpp` file and execute it to see your test results!\

> **Note:** You can use provided sample `CMakeLists.txt` file to compile your tests with `cmake` too.

Demo
---
For demo download/clone and compiler-execute [this](https://github.com/dariushha/cpptester-demo).
