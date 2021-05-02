Lizard
===

A lightweight and efficient C++ testing package.

Demo
---
![lizard C++ testing package demo](demo.gif)


```bash
git clone https://github.com/alphamarket/lizard.git
cd lizard
mkdir build && cd build
cmake .. && make
./test
```

```c++
// lizard/tests/sample_tester.hpp
#pragma once

#include "lizard/tester.hpp"

TEST(sample_tester, "Tester/Sample",
    int some_var_to_use_inside_specs = 1;

    void tester_method() const;
) {
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

    spec("sum", [&]() {
        IS_EQUAL(some_var_to_use_inside_specs++ + 2, 3);
    });

    spec("multiply", []() {
        SKIP_WITH_MESSAGE("SKIP WITH MESSAGE");
    });

    spec("minus", [&]() {
        IS_ZERO(some_var_to_use_inside_specs - 2);
    });

    spec("faulty", []() {
        IS_EQUAL(2 / 2, -1);
    });

    spec("divide", [&]() {
        tester_method();
        IS_EQUAL(2 / 2, 1);
    });
}

void LIZARD_TESTER_METHOD(sample_tester, tester_method)() const {
    std::cout << "Tester method got called!\n";
}
```

Event handlers
---
You can set some event handlers to catch up with the testing procedures, The list of events is as follow:

| Event | Description | Callback Signature |
|-------|-------------|--------------------|
| `onstart` | Get called before starting any `spec` unit (right at the begining of the test unit.) -- suitable to loading resources before test unit. | `std::function<void()>`  |
| `onterminate` | Get called after `spec`s are done (right at the terminating the test unit / regardless of the termination status.) -- suitable to releasing resources at the end of test unit. | `std::function<void()>` |
| `prespec` | Get invoked right before a `spec` get started. The callback function's arguments are the `name` of the spec is going to get executed -- suitable to loading resources at the start of each `spec`. | `std::function<void(const std::string&)>` |
| `postspec` | Get invoked right after a `spec` get *finished* / *skipped* / *failed*. The callback function's arguments are the `name` of the spec dealt with -- suitable to releasing resources at the end of each `spec`. | `std::function<void(const std::string&)>` |

Prerequisites
---
No prerequisites is needed. The project is as is.

How to step up in your project?
-----
Assume you have a project named `cppApp` written in C++.

There is a [setup script](https://raw.githubusercontent.com/alphamarket/lizard/master/lizard-setup) provided to make cloning this C++ Tester repository into your project easier

```BASH
cd "/path/to/cppApp"
curl https://raw.githubusercontent.com/alphamarket/lizard/master/lizard-setup | bash
# That is it.
cd test
```
