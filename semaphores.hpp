#ifndef __SEMAPHORES_H
#define __SEMAPHORES_H

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <thread>
#include <stdexcept>

class Semaphore {
private:
    std::uint64_t private_state;
    std::atomic<std::uint64_t> state;
public:
    Semaphore(std::uint64_t count, std::uint64_t limit);
    std::uint64_t get_limit();
    std::uint64_t get_count();
    void set_limit(std::uint64_t limit);

    void release(std::uint64_t n);
    void acquire(std::uint64_t n);
    bool try_acquire(std::uint64_t n);
};

#endif //__SEMAPHORES_H