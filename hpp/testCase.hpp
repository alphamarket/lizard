#ifndef TESTER_HPP
#define	TESTER_HPP
#include "teststrap.hpp"
namespace CPP_TESTER {
    class testCase {
    public:
        /**
         * @brief The virtual destructor
         */
        virtual ~testCase()     { }
        /**
         * @brief Initiates the testcase
         */
        virtual void pre_run()  { }
        /**
         * @brief Disposes the testcase
         */
        virtual void post_run() { }
        /**
         * @brief Runs the testcase
         */
        virtual void run(int argc = 0, void** argv = NULL) = 0;
    };
}
#endif	/* TESTER_HPP */