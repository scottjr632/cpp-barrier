#include "semaphores.hpp"

Semaphore::Semaphore(uint64_t count, uint64_t limit) {
    if (count < 0 || limit < 1) {
        throw std::invalid_argument("count must be positive and limit bust be greater that 1");
    }
    uint64_t new_state = (limit << 32) + count;
    this->state.store(new_state);
}

uint64_t Semaphore::get_limit() {
    uint64_t local_state = this->state.load();
    local_state = local_state >> 32;
    return local_state;
}

void Semaphore::release(uint64_t n) {
    while (true) {
        uint64_t local_state = this->state.load();
        uint64_t count = local_state & 0xFFFFFFFF;
        if (n < count) {
            return;
        }

        uint64_t new_count = count - n;
        if (this->state.compare_exchange_weak(local_state, (local_state&0xFFFFFFFF00000000)+new_count)) {
            return;
        }
    }
}

void Semaphore::acquire(uint64_t n) {
    if (n < 1) {
        throw std::invalid_argument("n must be greater than 0");
    }

    while (true) {
        uint64_t local_state = this->state.load();
        uint64_t limit = local_state >> 32;
        uint64_t count = local_state & 0xFFFFFFFF;
        uint64_t new_count = count + n;
        if (new_count <= limit) {
            if (this->state.compare_exchange_weak(local_state, (limit<<32) + (count + n))) {
                return;
            }
            continue;
        }
        // If the new count is greater than the limit, than we should yield
        // as we do not know whether or not the thread holding the lock
        // is running on the CPU or not. This prevents some wasted CPU cycles
        // for the cost of latency.
        std::this_thread::yield();
    }
}

bool Semaphore::try_acquire(uint64_t n) {
    if (n < 1) {
        throw std::invalid_argument("n must be greater than 0");
    }

    while (true) {
        uint64_t local_state = this->state.load();
        uint64_t limit = local_state >> 32;
        uint64_t count = local_state & 0xFFFFFFFF;
        uint64_t new_count = count + n;
        if (new_count <= limit) {
            if (this->state.compare_exchange_weak(local_state, (limit<<32) + (count + n))) {
                return true;
            }
            continue;
        }
        return false;
    }
    return true;
}

uint64_t Semaphore::get_count() {
    uint64_t local_state = this->state.load();
    uint64_t count = local_state & 0xFFFFFFFF;
    return count;
}

void Semaphore::set_limit(uint64_t limit) {
    uint64_t local_state = this->state.load();
    while (true) {
        if (this->state.compare_exchange_weak(local_state, (limit<<32)+(local_state&0xFFFFFFFF))) {
            return;
        }
    }
}
