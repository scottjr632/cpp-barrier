#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <set>
#include <mutex>

#include <doctest.h>
#include <barrier/barrier.hpp>


std::mutex m;
barrier::Barrier barr(3);
std::vector<int> stuff;

void doThing(int id, int iters)
{
    for (int i = 0; i < iters; i++)
    {
        {
            std::lock_guard<std::mutex> lk(m);
            stuff.push_back(id);
        }
        barr.ArriveAndWait();
    }
}

TEST_CASE("Ping Pong") {
    int iters = 25;
    std::thread pt(doThing, 0, iters);
    std::thread pp(doThing, 1, iters);
    std::thread pq(doThing, 2, iters);

    pt.join();
    pp.join();
    pq.join();

    CHECK(stuff.size() == (iters * 3));

    for (int i = 0; i < iters; i += 3)
    {
        std::set<int> s;
        for (int id = 0; id < 3; id++)
        {
            if (s.find(stuff[i+id]) != s.end())
                FAIL("INVALID BARRIER!", stuff[i+id]);

            s.insert(stuff[i+id]);
        }
        s.clear();
    }
}