#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

#include <doctest.h>
#include <rezsem/rezsemaphores.hpp>


std::atomic<uint64_t> ai;
rezsem::Semaphore pingSem(0, 1);
rezsem::Semaphore pongSem(1, 1);
std::vector<std::string> pingPongs;

void ping(int iters) {
    for (int i = 0; i < iters; i++) {
        pingSem.Acquire();
        pingPongs.push_back("ping");
        pongSem.Release();
    }
}

void pong(int iters) {
    for (int i = 0; i < iters; i++) {
        pongSem.Acquire();
        pingPongs.push_back("pong");
        pingSem.Release();
    }
}

TEST_CASE("Ping Pong") {
    int iters = 50;
    std::thread pt(ping, iters);
    std::thread pp(pong, iters);

    pt.join();
    pp.join();

    CHECK(pingPongs.size() == (iters * 2));

    for (int i = 0; i < (iters * 2); i++) {
        if (i % 2 == 0) {
            CHECK(pingPongs[i] == "ping");
        } else {
            CHECK(pingPongs[i] == "pong");
        }
    }
}