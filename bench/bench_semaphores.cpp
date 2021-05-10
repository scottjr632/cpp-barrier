#include <nanobench.h>
#include <rezsem/rezsemaphores.hpp>

#include <atomic>

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

int main() {
    int iters = 100;

    ankerl::nanobench::Bench().run("ping-pong 50 iterations", [&] {
        std::thread pt(ping, iters);
        std::thread pp(pong, iters);

        pt.join();
        pp.join();
    });
}