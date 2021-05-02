# RezSem Tests

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
$ cmake ../. -G "Visual Studio 15 2017"
```

- Open REZSEM.sln
- Build tests in RELEASE | x64
- Run tests.exe
