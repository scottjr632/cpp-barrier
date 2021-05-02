#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <thread>
#include <stdexcept>

namespace rezsem
{

using namespace std;

class Semaphore
{
    unsigned int n_threads_;
    uint64_t private_state_;
    atomic<uint64_t> state_;

public:
    Semaphore(uint64_t count, uint64_t limit) :
            n_threads_(thread::hardware_concurrency())
    {
        if (count < 0 || limit < 1) {
            throw std::invalid_argument("count must be positive and limit must be greater than 1");
        }
        uint64_t new_state = (limit << 32) + count;
        state_.store(new_state);
    }

    uint64_t GetLimit() {
        uint64_t local_state = state_.load();
        local_state = local_state >> 32;
        return local_state;
    }

    void Release() { Release(1); }

    void Release(uint64_t n) {
        while (true) {
            uint64_t local_state = state_.load();
            uint64_t count = local_state & 0xFFFFFFFF;
            if (n < count) {
                return;
            }

            uint64_t new_count = count - n;
            if (state_.compare_exchange_weak(local_state, 
                (local_state & 0xFFFFFFFF00000000) + new_count)) {
                 return;
            }
        }
    }

    void Acquire() { Acquire(1); }

    void Acquire(uint64_t n) {
        if (n < 1) {
            throw invalid_argument("n must be greater than 0");
        }

        while (true) {
            uint64_t local_state = state_.load();
            uint64_t limit = local_state >> 32;
            uint64_t count = local_state & 0xFFFFFFFF;
            uint64_t new_count = count + n;
            if (n > limit) {
                throw std::invalid_argument("n cannot be greater than the limit");
            }

            if (new_count <= limit) {
                if (this->state_.compare_exchange_weak(local_state,
                     (limit<<32) + (count + n))) {
                    return;
                }
                continue;
            }

            // If there is only one CPU available or if there are more locks acquired
            // than can be running on the available CPUs then we should yield this
            // thread to another process that can run. This is because the thread that
            // holds the lock might not be running and by spinning we ar just wasting
            // cpu cycles. However,if there are more available CPUs than threads holding
            // a lock then we should just spin hoping that we get lock earlier due to
            // gang scheduling.
            if (n_threads_ == 1 || n_threads_ < new_count) {
                std::this_thread::yield();
            }
        }
    }

    bool TryAcquire() { return TryAcquire(1); }

    bool TryAcquire(uint64_t n) {
        if (n < 1) {
            throw invalid_argument("n must be greater than 0");
        }

        while (true) {
            uint64_t local_state = state_.load();
            uint64_t limit = local_state >> 32;
            uint64_t count = local_state & 0xFFFFFFFF;
            uint64_t new_count = count + n;
            if (new_count <= limit) {
                if (state_.compare_exchange_weak(local_state,
                     (limit<<32) + (count + n))) {
                    return true;
                }
                continue;
            }
            return false;
        }
        return true;
    }


    uint64_t GetCount() {
        uint64_t local_state = state_.load();
        uint64_t count = local_state & 0xFFFFFFFF;
        return count;
    }

    void SetLimit(uint64_t limit) {
        uint64_t local_state = state_.load();
        while (true) {
            if (state_.compare_exchange_weak(local_state,
                (limit << 32) + (local_state & 0xFFFFFFFF))) {
                 return;
            }
        }
    }
};

}
