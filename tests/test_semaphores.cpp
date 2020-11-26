#include <iostream>
#include <vector>

#include "utils.h"
#include "current_function.hpp"
#include "../semaphores.hpp"

class TestSemaphore {
public:
    void run_all() {
        this->acquire();
        this->acquire_throwsException_negativeN();
        this->try_acquire_shouldReturnFalseWhenFull();
        this->try_acquire_shouldReturnTrueWhenNotFull();
    }
    void acquire_throwsException_negativeN() {
        Semaphore s(1, 1);
        try {
            s.acquire(0);
            s.acquire(-1);
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
            pass(e.what());
            return;
        }

        fail("Aquire should have thrown error");
    }
    void acquire() {
        Semaphore s(0, 1);
        try {
            s.acquire(1);
            if (s.get_count() != 1) {
                fail("limit should be zero");
                std::cout << "got " << s.get_count() << std::endl;
                return;
            }
        } catch (const std::exception& e) {
            fail(e.what());
            return;
        }
        pass("");
    }

    void try_acquire_shouldReturnFalseWhenFull() {
        Semaphore s(0, 1);
        try {
            if (s.try_acquire(2)) {
                fail("try acquire should have failed to acquire 2");
                return;
            }
            pass("");
        } catch(const std::exception& e) {
            fail(e.what());
        }
    }

    void try_acquire_shouldReturnTrueWhenNotFull() {
        Semaphore s(0, 1);
        try {
            if (s.try_acquire(1)) {
                pass("");
                return;
            }
            fail("try_acquire should have obtained 1 semaphore");
        } catch(const std::exception& e) {
            fail(e.what());
        }
    }
};


int main() {
    TestSemaphore ts;
    ts.run_all();
}