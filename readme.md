# C++ Tutorial
Setting up VSCode
## Unix
1. Install GCC, gdb, and cmake
```bash
sudo apt-get update
sudo apt-get install build-essential gdb cmake
```
2. Check `gcc` and `cmake` versions.
```bash
jpt@100834-pc:~/git/cpp_trial$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
...
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)

jpt@100834-pc:~/git/cpp_trial/build$ cmake --version
cmake version 3.16.3
```

## Usage
This uses `cmake` to create a make file. See the `CMakeLists.txt` for instructions on how the make file is generated.

1. `git clone XXXX`
2. `cd cpp_trial`
3. Download [Eigen 3.4.0](https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz)
4. Untar and put in external_include folder.
5. `mkdir build`
6. `cd build`
7. `cmake ..`
8. `make`
9. run `./my_program ../data/load.csv`

## Debugging
I have included a `launch.json` and `tasks.json` in the `.vscode` folder. Launch sets up the program to run and tasks include the pre launch tasks it must execute. This includes running `cmake` with the debug flag.

## References
1. [Setup C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp)
2. [Eigen C++ Template Library](https://eigen.tuxfamily.org/index.php?title=Main_Page)
3. [Setting up gdb with make file in VS Code](https://hackernoon.com/how-to-set-up-c-debugging-in-vscode-using-a-makefile)