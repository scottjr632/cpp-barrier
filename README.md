# RezSem - Resizable Semaphores

<p>
  <a href="https://github.com/scottjr632/resizable-semaphores/actions/workflows/ci.yml">
    <img src="https://github.com/scottjr632/resizable-semaphores/actions/workflows/ci.yml/badge.svg" alt="CI" />
  </a>
  <a href="https://github.com/p-ranav/argparse/blob/master/LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="license"/>
  </a>
  <img src="https://img.shields.io/badge/version-1.0.0-blue.svg?cacheSeconds=2592000" alt="version"/>
</p>

## Highlights

A fast adaptive semaphore lock implementation for cpp!

* Single header file
* MIT License
* Require C++17

## Quick Start

All you need to do is to include `rezsemaphores.hpp` and you're good to go

```cpp
#include <rezsem/rezsemaphores.hpp>
```

You can either grab the latest [version](https://raw.githubusercontent.com/scottjr632/resizable-semaphores/v1.0.0/include/rezsem/rezsemaphores.hpp) or clone the repository and include the `include` directory.

Example

```bash
$ wget https://raw.githubusercontent.com/scottjr632/resizable-semaphores/v1.0.0/include/rezsem/rezsemaphores.hpp -P rezsem
```

## Usage

Semaphores can be initialized 

```cpp
rezsem::Semaphore s(<initial count>, <limit>);
```

You can acquire a semaphore by using the `Acquire` method.
Acquire will block until the requested number of locks are acquired.

```cpp
rezsem::Semaphore s(<initial count>, <limit>);

s.Acquire(); // will be default increment count by one
s.Acquire(n); // will increment the count by `n`
```

If you do not want to block waiting on a lock to become free, you can use the
`TryAcquire(n)` or `TryAcquire()` methods.

```cpp
rezsem::Semaphore s(<initial count>, <limit>);

s.TryAcquire(); // will not block. Will return true if lock is acquired or false if not
```

To release the lock you can use

```cpp
s.Release(); // Releases one by default
s.Release(n); // Releases N
```

Resizing the limit of the semaphore can be done using 

```cpp
s.SetLimit(n); // s.GetLimit() == n
```

## Examples

For examples please see the [tests/test_*.cpp](./tests) files.
