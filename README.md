# RezSem - Resizable Semaphores

A fast resizable semaphore implementation for cpp!

## Installing

The easiest way to currently install the rezsem library is using `cmake` and install the library into a local path.

### Setup

It is best to install this library to a local path instead of a system path. For the rest of the instillation guide the environment variable `MY_INSTALL_DIR` will hold the local path.

```bash
$ export MY_INSTALL_DIR=$HOME/.local
```

Create the local path if it doesn't exists:

```bash
$ mkdir -p $MY_INSTALL_DIR
```

Add the local `bin` to your path:

```bash
$ export PATH="$PATH:$MY_INSTALL_DIR/bin"
```

### Installing cmake

RezSem needs `cmake version >= 3.10`. This can be checked by running `cmake --version`.

In general `cmake` can be installed

- Linux
  ```bash
  $ sudo apt install cmake
  ```
- MacOS
  ```bash
  $ brew install cmake
  ```

### Installing other required tools

- Linux

  ```bash
  $ sudo apt install -y build-essential autoconf libtool pkg-config
  ```
- macOS
  ```bash
  $ brew install autoconf automake libtool pkg-config
  ```

### Clone the `rezsem` repo

```bash
$ git clone https://github.com/scottjr632/resizable-semaphores.git
```

### Build and install `rezsem`

The following commands will build and locally install `rezsem`.

```bash
$ mkdir -p cmake/build
$ pushd cmake/build
$ cmake \
  -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
  ../..
$ make
$ make install
$ popd
```