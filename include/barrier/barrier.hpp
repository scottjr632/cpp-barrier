#pragma once

#include <atomic>
#include <stdint.h>
#include <thread>
#include <stdexcept>

namespace barrier
{
using namespace std;

class Barrier
{
  uint64_t _count;
  atomic_bool _sense;
  atomic<uint64_t> _n;

public:
  Barrier(uint64_t count): _count(count)
  {
    _n.store(count);
  }

  void ArriveAndWait()
  {
    bool priv_sense = _sense.load();
    if (_n.fetch_sub(1) == 1)
    {
      _n.store(_count);
      _sense.store(!priv_sense);
    }
    else
    {
      while (priv_sense == _sense.load());
    }
  }
};

}