#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

#include "../rezsemaphores.hpp"
#include "utils.h"

#define MAX 25

std::atomic<uint64_t> ai;

Semaphore pingSem(0, 1);
Semaphore pongSem(1, 1);
std::vector<std::string> pingPongs;


void ping() {
    for (int i = 0; i < MAX; i++) {
        pingSem.acquire(1);
        std::cout << "ping -> ";
        pingPongs.push_back("ping");
        pongSem.release(1);
    }
}

void pong() {
    for (int i = 0; i < MAX; i++) {
        pongSem.acquire(1);
        pingPongs.push_back("pong");
        std::cout << "pong" << std::endl;
        pingSem.release(1);
    }
}

int main() {
    std::thread pt(ping);
    std::thread pp(pong);

    pt.join();
    pp.join();

    if (pingPongs.size() != (MAX * 2)) {
        fail("pingPongs is not the correct size got");
        return 0;
    }

    for (int i = 0; i < MAX * 2; i++) {
        if (i % 2 == 0) {
            if (pingPongs[i] != "ping") {
                fail("expected ping but didnt get");
                return 0;
            }
        } else {
            if (pingPongs[i] != "pong") {
                fail("expected pong");
                return 0;
            }
        }
    }

    pass("");
}