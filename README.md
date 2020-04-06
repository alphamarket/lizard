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
```


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
