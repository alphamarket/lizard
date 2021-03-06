#pragma once

#define LIZARD_VERSION "2.1.0"

#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
#include <typeinfo>
#include <exception>
#include <unordered_map>
#if __cplusplus >= 201103L
#   include <type_traits>
#endif

namespace lizard {
    class TestFailException : public std::runtime_error {
        size_t _line;
        std::string _file;
    public:

        TestFailException(const char* const error, const char* const file = "", const size_t& line = 0)
            : runtime_error(error), _line(line), _file(file)
        { }

        const size_t& line() const { return _line; }
        const std::string& file() const { return _file; }
    };

    class TestSkipException : public std::runtime_error {
        size_t _line;
        std::string _file;
    public:

        TestSkipException(const char* const error = "", const char* const file = "", const size_t& line = 0)
            : runtime_error(error), _line(line), _file(file)
        { }

        const size_t& line() const { return _line; }
        const std::string& file() const { return _file; }
    };
}

/**
 * Makes sure the input is true
 */
#define BESURE(o) { if(!(o)) { throw lizard::TestFailException(("Failed to assert: " + std::string(#o)).c_str(), __FILE__, __LINE__); } }
/**
 * Failure assertion with message
 */
#define FAIL(o) throw lizard::TestFailException(#o, __FILE__, __LINE__)
/**
 * Makes sure the arguments are eqaul
 */
#define IS_EQUAL(o, z) BESURE((o) == (z))
/**
 * Makes sure the arguments are NOT eqaul
 */
#define NOT_EQUAL(o, z) BESURE((o) != (z))
/**
 * Makes sure the arguments are eqaul
 */
#define SHOULD_BE(o, z) IS_EQUAL(o, z)
/**
 * Makes sure the arguments are NOT eqaul
 */
#define SHOULD_NOT_BE(o, z) NOT_EQUAL(o, z)
/**
 * Makes sure the arguments are eqaul
 */
#define IS_SAME(o, z) IS_EQUAL(o, z)
/**
 * Makes sure the arguments are NOT eqaul
 */
#define NOT_SAME(o, z) NOT_EQUAL(o, z)
/**
 * Makes sure the argument is NOT null
 */
#define NOT_NULL(o) NOT_EQUAL(o,  NULL)
/**
 * Makes sure the argument is NULL
 */
#define IS_NULL(o) IS_EQUAL(o,  NULL)
/**
 * Makes sure the argument is IS_EQUAL to zero
 */
#define IS_ZERO(o) IS_EQUAL(o, 0)
/**
 * Makes sure the argument is NOT IS_EQUAL to zero
 */
#define NOT_ZERO(o) NOT_EQUAL(o, 0)
/**
 * Makes sure the argument is true
 */
#define IS_TRUE(o) IS_EQUAL(o, true)
/**
 * Makes sure the argument is NOT true
 */
#define NOT_TRUE(o) IS_EQUAL(o, false)
/**
 * Makes sure the argument is false
 */
#define IS_FALSE(o) IS_EQUAL(o, false)
/**
 * Makes sure the argument is NOT false
 */
#define NOT_FALSE(o) IS_EQUAL(o, true)
/**
 * Makes sure the arguments are same type
 */
#define IS(o, z) IS_EQUAL(typeid(o).name(), typeid(z).name())
/**
 * Makes sure the arguments are NOT same type
 */
#define IS_NOT(o, z) NOT_EQUAL(typeid(o).name(), typeid(z).name())
/**
 * Makes sure the argument is a pointer
 */
#define IS_POINTER(o) IS_EQUAL(typeid(o).name()[0], 'P')
/**
 * Makes sure the argument is NOT a pointer
 */
#define NOT_POINTER(o) NOT_EQUAL(typeid(o).name()[0], 'P')
/**
 * Makes sure the arguments WHICH ARE POINTERS are pointing same location
 */
#define PSAME_POINT(o, z) IS_SAME(o, z)
/**
 * Makes sure the arguments WHICH ARE {NOT} POINTERS are pointing same location
 */
#define NSAME_POINT(o, z) IS_SAME(&o, &z)
/**
 * Makes sure the arguments WHICH ARE POINTERS are NOT pointing same location
 */
#define PNOT_SAME_POINT(o, z) NOT_SAME(o, z)
/**
 * Makes sure the arguments WHICH ARE {NOT} POINTERS are NOT pointing same location
 */
#define NNOT_SAME_POINT(o, z) NOT_SAME(&o, &z);
/**
 * Makes sure if after executing the passed argument an exception will be thrown
 */
#define SHOULD_THROW(...) \
try { \
    __VA_ARGS__; \
    FAIL("Expecting to catch something, but didn't get one!"); \
} catch(const lizard::TestFailException&) { throw; } catch(...) { }
/**
 * Makes sure if after executing the passed argument an exception does NOT get thrown
 */
#define SHOULD_NOT_THROW(...) \
try { \
    __VA_ARGS__; \
} catch(...) { FAIL("Wasn't expecting to catch something, but got one!"); }
/**
 * Makes sure the arguments are eqaul
 */
#define ASSERT_IS_EQUAL(o, z) IS_EQUAL(o, z)
/**
 * Makes sure the arguments are NOT eqaul
 */
#define ASSERT_NOT_EQUAL(o, z) NOT_EQUAL(o, z)
/**
 * Makes sure the arguments are eqaul
 */
#define ASSERT_SAME(o, z) IS_SAME(o, z)
/**
 * Makes sure the arguments are NOT eqaul
 */
#define ASSERT_NOT_SAME(o, z) NOT_SAME(o, z)
/**
 * Makes sure the argument is NOT null
 */
#define ASSERT_NOT_NULL(o) NOT_NULL(o)
/**
 * Makes sure the argument is NULL
 */
#define ASSERT_NULL(o) IS_NULL(o)
/**
 * Makes sure the argument is IS_EQUAL to zero
 */
#define ASSERT_ZERO(o) IS_ZERO(o)
/**
 * Makes sure the argument is NOT IS_EQUAL to zero
 */
#define ASSERT_NOT_ZERO(o) NOT_ZERO(o)
/**
 * Makes sure the argument is true
 */
#define ASSERT_TRUE(o) IS_TRUE(o)
/**
 * Makes sure the argument is NOT true
 */
#define ASSERT_NOT_TRUE(o) NOT_TRUE(o)
/**
 * Makes sure the argument is false
 */
#define ASSERT_FALSE(o) IS_FALSE(o)
/**
 * Makes sure the argument is NOT false
 */
#define ASSERT_NOT_FALSE(o) NOT_FALSE(o)
/**
 * Makes sure the arguments are same type
 */
#define ASSERT_IS(o, z) IS(o, z)
/**
 * Makes sure the arguments are NOT same type
 */
#define ASSERT_IS_NOT(o, z) IS_NOT(o, z)
/**
 * Makes sure the argument is a pointer
 */
#define ASSERT_POINTER(o) IS_POINTER(o)
/**
 * Makes sure the argument is NOT a pointer
 */
#define ASSERT_NOT_POINTER(o) NOT_POINTER(o)
/**
 * Makes sure the arguments WHICH ARE POINTERS are pointing same location
 */
#define ASSERT_PSAME_POINT(o, z) PSAME_POINT(o, z)
/**
 * Makes sure the arguments WHICH ARE {NOT} POINTERS are pointing same location
 */
#define ASSERT_NSAME_POINT(o, z) NSAME_POINT(o, z)
/**
 * Makes sure the arguments WHICH ARE POINTERS are pointing same location
 */
#define ASSERT_PNOT_SAME_POINT(o, z) PNOT_SAME_POINT(o, z)
/**
 * Makes sure the arguments WHICH ARE {NOT} POINTERS are pointing same location
 */
#define ASSERT_NNOT_SAME_POINT(o, z) NNOT_SAME_POINT(o, z)
/**
 * Failure assertion
 */
#define ASSERT_FAILURE FAIL

#if __cplusplus >= 201103L
/**
 * Makes sure the "o" is inherited from "b"
 */
#define IS_BASE_OF(b, o) 							\
  ((std::is_base_of<b, o>::value)								\
   ? __ASSERT_VOID_CAST (0)						\
   : FAIL("type inheritance assertion failure!"))
#endif

#ifdef __unix__
    #define COLORIFY(c, o) std::string(c) + o + std::string("\x1b[m")
    #define MKCOLOR(c) std::string("\x1b[" + std::string(#c) + "m")
#else
    #define COLORIFY(c, o) o
    #define MKCOLOR(c)
#endif

#define TEST(func) \
    std::cout << COLORIFY(MKCOLOR(32), "  Testing ") << #func; \
    this->test_##func(); \
    std::cout << COLORIFY(MKCOLOR(32), " [OK]") << std::endl << std::flush

#include <functional>

#define TESTER(test_suite_name, ...) namespace lizard { namespace test { \
    class test_suite_name : public lizard_base_tester { \
        std::vector<std::pair<std::string, std::function<void()>>> __tests; \
        std::unordered_map<std::string, std::function<void()>> __triggers; \
        std::unordered_map<std::string, std::function<void(const std::string&)>> __triggers_spec; \
        std::unordered_map<std::string, std::function<void(const std::string&, const std::exception&)>> __triggers_error; \
    public: \
        void run() { \
            __VA_ARGS__ \
            size_t count = 0, warnings_count = 0;\
            auto handle_error = [&count](const auto& __tests, const auto& t) { \
                std::cout << "\r" << COLORIFY(MKCOLOR(31), "  \u2613 Testing ") << t.first << " " << COLORIFY(MKCOLOR(41) + MKCOLOR(5), "[FAILED]"); \
                if(count < __tests.size()) \
                    std::cout << " " << COLORIFY(MKCOLOR(31), "[" << __tests.size() - count << " remaining tests skipped!]"); \
                std::cout << std::endl << std::flush; \
            }; \
            if(__triggers.count("before")) \
                __triggers["before"](); \
            for(auto& t : __tests) { \
                count += 1; \
                try { \
                    std::cout << COLORIFY(MKCOLOR(32), "  Testing ") << t.first; \
                    if(__triggers_spec.count("prespec")) \
                        __triggers_spec["prespec"](t.first); \
                    t.second(); \
                    if(__triggers_spec.count("postspec")) \
                        __triggers_spec["postspec"](t.first); \
                    std::cout << "\r" << COLORIFY(MKCOLOR(32), "  \u221A Testing ") << t.first << std::endl << std::flush; \
                } catch(lizard::TestSkipException& e) { \
                    if(__triggers_spec.count("postspec")) \
                        __triggers_spec["postspec"](t.first); \
                    if(__triggers_error.count("onskip")) \
                        __triggers_error["onskip"](t.first, e); \
                    std::cout << "\r" << COLORIFY(MKCOLOR(33), "  🛇 Testing ") << t.first << " " << COLORIFY(MKCOLOR(43) + MKCOLOR(5), "[SKIPPED]") << std::endl \
                              << "    File: " << e.file() << ":" << e.line() << std::endl; \
                    if(std::string(e.what()).size() > 0) \
                        std::cout << "    Message: " << e.what() << std::endl; \
                    std::cout << std::flush; \
                    warnings_count += 1; \
                } catch(lizard::TestFailException& e) { \
                    if(__triggers_spec.count("postspec")) \
                        __triggers_spec["postspec"](t.first); \
                    if(__triggers_error.count("onfail")) \
                        __triggers_error["onfail"](t.first, e); \
                    handle_error(__tests, t); \
                    if(__triggers.count("after")) \
                        __triggers["after"](); \
                    throw e; \
                } catch(std::exception& e) { \
                    if(__triggers_spec.count("postspec")) \
                        __triggers_spec["postspec"](t.first); \
                    if(__triggers_error.count("onfail")) \
                        __triggers_error["onfail"](t.first, e); \
                    handle_error(__tests, t); \
                    if(__triggers.count("after")) \
                        __triggers["after"](); \
                    throw lizard::TestFailException(e.what(), __FILE__); \
                } \
            } \
            if(__triggers.count("after")) \
                __triggers["after"](); \
            if(warnings_count > 0) SKIP(); \
        } \
    }; } } \

#define SKIP() throw lizard::TestSkipException("", __FILE__, __LINE__)
#define SKIP_WITH_MESSAGE(s) throw lizard::TestSkipException(#s, __FILE__, __LINE__)
#define spec(func, ...) __tests.push_back(std::make_pair(#func, __VA_ARGS__))
#define spec_s(func, ...) __tests.push_back(std::make_pair(func, __VA_ARGS__))
#define mktrigger2(key, ...) __triggers[#key] = __VA_ARGS__
#define mktrigger3(type, key, ...) __triggers_##type[#key] = __VA_ARGS__
#define onbefore(...) mktrigger2(before, __VA_ARGS__)
#define onafter(...) mktrigger2(after, __VA_ARGS__)
#define onskip(...) mktrigger3(error, onskip, __VA_ARGS__)
#define onfail(...) mktrigger3(error, onfail, __VA_ARGS__)
#define onprespec(...) mktrigger3(spec, prespec, __VA_ARGS__)
#define onpostspec(...) mktrigger3(spec, postspec, __VA_ARGS__)

namespace lizard {
    class lizard_base_tester {
    public:
        /**
         * @brief Runs the testcase
         */
        virtual void run() = 0;
        /**
         * @brief The virtual destructor
         */
        virtual ~lizard_base_tester() { }
    };

    typedef std::pair<std::string, lizard_base_tester*> test_case;

    class lizard_registery {
        static lizard_registery* self;
        std::vector<test_case> _registery;
    public:
        static void close() { delete self; }
        static lizard_registery* instance() { return self; }
        static size_t size() { return self->_registery.size(); }
        static std::vector<test_case>& container() { return self->_registery; }
        static void push(const test_case& tc) { self->_registery.push_back(tc); }
        static test_case* at(const size_t& index) { return &self->_registery[index]; }
        static lizard_registery* open() { self = new lizard_registery(); return self; }
    };
    lizard_registery* lizard_registery::self = lizard_registery::open();
}

#define lizard_register_custom(label, name) ::lizard::lizard_registery::push(test_case(label, new name))
#define lizard_register(name) lizard_register_custom(string(#name), name)
#define $(label, name) lizard_register_custom(label, name)

#define MANIFEST(...) namespace lizard { void lizard_manifest () { __VA_ARGS__ } }
