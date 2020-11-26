#ifndef __SEMAPHORES_UTILS_H
#define __SEMAPHORES_UTILS_H

#include <iostream>
#include <typeinfo>
#include "current_function.hpp"

#define pass(msg) do { std::cout << BOOST_CURRENT_FUNCTION << "\nTest passed: " << msg << std::endl; } while(0) 
#define fail(msg) do { std::cout << BOOST_CURRENT_FUNCTION << "\n[" << __LINE__ << "] " << "Test failed: " << msg << std::endl; } while(0) 

#endif //__SEMAPHORES_UTILS_H