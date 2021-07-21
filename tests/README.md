# RezSem Tests

Tests can be compiled by using CMake from the root directory.

## Linux

```bash
$ mkdir build && cd $_
$ cmake ../.
$ make
$ ./tests
```

## Windows

```powershell
$ mkdir build
$ cd build
$ cmake ../.
$ msbuild rezsem.sln
$ .\tests\Debug\tests.exe
```