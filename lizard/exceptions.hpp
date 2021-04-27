#pragma once

#include <stdexcept>

namespace lizard {
/**
 * @brief The LizardTestFailError class gets sent when a test unit is failing
 */
class LizardTestFailError : public std::runtime_error {
    size_t _line;
    std::string _file;
public:

    LizardTestFailError(const char* const error, const char* const file = "", const size_t& line = 0)
        : runtime_error(error), _line(line), _file(file)
    { }

    const size_t& line() const { return _line; }
    const std::string& file() const { return _file; }
};
/**
 * @brief The LizardTestSkipError class gets sent when skipping a test unit
 */
class LizardTestSkipError : public std::runtime_error {
    size_t _line;
    std::string _file;
public:

    LizardTestSkipError(const char* const error = "", const char* const file = "", const size_t& line = 0)
        : runtime_error(error), _line(line), _file(file)
    { }

    const size_t& line() const { return _line; }
    const std::string& file() const { return _file; }
};
/**
 * @brief The LizardRuntimeError class general lizard exception
 */
class LizardRuntimeError : public std::runtime_error {
public:
    LizardRuntimeError(const std::string& error)
        : std::runtime_error(error)
    { }
};

}
