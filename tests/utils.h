#ifndef __SEMAPHORES_UTILS_H
#define __SEMAPHORES_UTILS_H

#include <iostream>
#include <typeinfo>
#include "current_function.hpp"

#define pass(msg) do { std::cout << "\nTest passed: " << BOOST_CURRENT_FUNCTION << " :" << msg << std::endl; } while(0)
#define fail(msg) do { std::cout << "Test failed: " << BOOST_CURRENT_FUNCTION << " [" << __LINE__ << "] " << msg << std::endl; } while(0)

#define assert_equals(val, val_two, msg) \
do { \
    if (val != val_two) fail(msg); \
} while(0)

#endif //__SEMAPHORES_UTILS_H