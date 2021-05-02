#include <iostream>
#include <doctest.h>
#include <rezsem/rezsemaphores.hpp>

using doctest::test_suite;
using namespace std;

TEST_CASE("Throws exception when negative N") {
    rezsem::Semaphore s(1, 1);
    try
    {
        s.Acquire(0);
        s.Acquire(-1);
        FAIL("Should have failed");
    }
    catch(const std::exception& e) {}
}

TEST_CASE("Should throw an error if acquire more than limit") {
    rezsem::Semaphore s(0, 1);
    try
    {
        s.Acquire(5);
        FAIL("Should have thrown error. Over limit");
    }
    catch(const std::exception& e) {}
    
}

TEST_CASE("Limit should increment appropriately") {
    SUBCASE("should increment by one when one is acquired") {
        rezsem::Semaphore s(0, 5);
        s.Acquire(1);
        CHECK(s.GetCount() == 1);
    }

    SUBCASE("should increment by N specified") {
        rezsem::Semaphore s(0, 5);
        s.Acquire(3);
        CHECK(s.GetCount() == 3);
    }

    SUBCASE("should default increment by one if no N is provided") {
        rezsem::Semaphore s(0, 5);
        s.Acquire();
        CHECK(s.GetCount() == 1);
    }
}

TEST_CASE("TryAcquire") {
    SUBCASE("should return false if limit is reached") {
        rezsem::Semaphore s(0, 1);
        CHECK(s.TryAcquire(2) == false);
    }
    SUBCASE("should return true if limit is not reached") {
        rezsem::Semaphore s(0, 1);
        CHECK(s.TryAcquire(1) == true);
    }
    SUBCASE("should return true if N is not specified and limit is not reached") {
        rezsem::Semaphore s(0, 1);
        CHECK(s.TryAcquire() == true);
    }
}

TEST_CASE("Acquire and release") {
    rezsem::Semaphore s(0, 1);

    s.Acquire();
    CHECK(s.GetCount() == 1);

    s.Release();
    CHECK(s.GetCount() == 0);
}

TEST_CASE("Resizing the limit") {
    rezsem::Semaphore s(0, 1);
    CHECK(s.GetLimit() == 1);

    s.SetLimit(10);
    CHECK(s.GetLimit() == 10);

    CHECK(s.TryAcquire(5) == true);
    CHECK(s.TryAcquire(5) == true);
}