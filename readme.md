# C++ Tutorial
I managed to set this all up on a WSL with Ubuntu 20.04. The codebase requires the following:
* g++ >= 10.5
* gdb >= 9.2
* cmake >= 3.16.3
* Additional packages:
    ```
    sudo apt install build-essential libboost-all-dev libopenblas-dev liblapack-dev libarpack2-dev libsuperlu-dev libarmadillo-dev liblpsolve55-dev lp-solve pkg-config
    ```

There are several modules that I needed to build or download by myself too:
* mlpack == 4.3.0
* eigen >= 3.4
* cereal >= 1.3.2
* ensmallen >= 2.21.1

Toolboxes:
* [AI-Toolbox](https://github.com/Svalorzen/AI-Toolbox) commit 9314b92b50eaac47c17da5b08b00144b70e51747

## Installation and Setup
Move all downloaded tar files to some place on your local machine.

### Extract `Eigen`
```bash
tar -xzvf eigen-3.4.0.tar.gz
```

### Extract `cereal`
```bash
tar -xzvf cereal-1.3.2.tar.gz
```

### Build `ensmallen`
```
tar -xzvf ensmallen-2.21.1.tar.gz
cd ensmallen-2.21.1/
cmake -S . -B build
cd build/
make install
```

### Build `mlpack`
Modify the CMakeLists.txt at the root to add the following:
```cmake
set(CEREAL_INCLUDE_DIR "/home/jpt/libs/cereal-1.3.2/include")
```
Then build, this will place the built library in `mlpack-bin`:
```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/home/jpt/libs/mlpack-4.3.0/mlpack-bin
cmake --build build --target install
```

### Build `AI-Toolbox`
They suggest to make it a submodule, but i'm not yet sure how to do that.
```bash
git clone git@github.com:Svalorzen/AI-Toolbox.git
cd AI-Toolbox
```
Modify the CMakeLists.txt at root to comment and add the following at around line 140:
```cmake
#find_package(Eigen3 ${EIGEN_VERSION_REQUIRED} REQUIRED)
set(EIGEN3_INCLUDE_DIR "/home/jpt/libs/eigen-3.4.0")
```
Exit that and make sure you are at the root `~/git/AI-Toolbox` and start cmake
```bash
mkdir build
cd build
cmake ..
make
```

## Usage and Importing of Libraries to Workspace
Inside the CMakeLists.txt at the root of this project, make sure you modify and point the libraries to the following:
```cmake
# Change to the desired name of the output executable.
set(PROGRAM_NAME "my_program")

set(MLPACK_INCLUDE_DIR "/home/jpt/libs/mlpack-4.3.0/mlpack-bin/include")
set(EIGEN3_INCLUDE_DIR "/home/jpt/libs/eigen-3.4.0")
set(AITOOLBOX_INCLUDE_DIR "/home/jpt/git/AI-Toolbox/include")

# For MDP, repeat for POMDP and FMDP
set_target_properties(MyExternalLib PROPERTIES IMPORTED_LOCATION "/home/jpt/git/AI-Toolbox/build/libAIToolboxMDP.a")
```

To run the code, make sure you are at the root:
```bash
cmake -S . -B build
cd build
make
./my_program
```

## Test Cases
I used [GoogleTest](https://google.github.io/googletest/quickstart-cmake.html) here, see documentation to set it up. Some extra information for getting the external headers included in the test files. You need to add them to the `test/CMakeLists.txt`:
```cmake
# Needed to be able to reference external headers.
set(files
    ${PROJECT_SOURCE_DIR}/include/foo.h 
    ${PROJECT_SOURCE_DIR}/src/foo.cpp 
    ${PROJECT_SOURCE_DIR}/include/sample2.h 
    ${PROJECT_SOURCE_DIR}/src/sample2.cpp 
    )
# Then add to the add_executable
add_executable(
  hello_test
  hello_test.cpp
  ${files}
)
```
Simply build the code again and inside `./build/tests` run `ctests` and it should give you the results:
```bash
Test project /home/jpt/git/cpp_trial/build/tests
    Start 1: HelloTest.BasicAssertions
1/3 Test #1: HelloTest.BasicAssertions ........   Passed    0.00 sec
    Start 2: HelloTest.BasicAdd
2/3 Test #2: HelloTest.BasicAdd ...............   Passed    0.00 sec
    Start 3: MyString.DefaultConstructor
3/3 Test #3: MyString.DefaultConstructor ......   Passed    0.00 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.01 sec
```

## Debugging
I have included a `launch.json` and `tasks.json` in the `.vscode` folder. Launch sets up the program to run and tasks include the pre launch tasks it must execute. This includes running `cmake` with the debug flag.

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```
Once build for debugging, adding breakpoints and running under debug mode will work.

## Troubleshooting
There are several issues I encountered, mainly with libraries and how they are detected by VSCode.

### VSCode or C++ lint not detecting libraries
You need to update `c_cpp_properties.json` in `.vscode` folder or through the Microsoft C/C++ Extension UI: `> C/C++: Edit configurations (UI)`
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}",
                "/home/jpt/git/cpp_trial/include",
                "/home/jpt/libs/mlpack-4.3.0/mlpack-bin/include/**",
                "/home/jpt/libs/mlpack-4.3.0/mlpack-bin/include/mlpack/**",
                "/home/jpt/libs/mlpack-4.3.0/mlpack-bin/**",
                "/home/jpt/git/AI-Toolbox/include/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c17",
            "cppStandard": "c++20",
            "intelliSenseMode": "clang-x64",
            "configurationProvider": "ms-vscode.makefile-tools"
        }
    ],
    "version": 4
}
```

If VSCode still cannot detect, try uninstalling and reinstalling the C/C++ Extensions.

## References
1. [Setup C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp)
2. [Eigen C++ Template Library](https://eigen.tuxfamily.org/index.php?title=Main_Page)
3. [Setting up gdb with make file in VS Code](https://hackernoon.com/how-to-set-up-c-debugging-in-vscode-using-a-makefile)
4. [Getting started with mlpack](https://mccormickml.com/2017/02/01/getting-started-with-mlpack/) this is a third party older tutorial but it looks like it will work.
5. [Setting linker flags for openMP in cmake](https://stackoverflow.com/questions/12399422/how-to-set-linker-flags-for-openmp-in-cmakes-try-compile-function)
6. [AI-Toolbox](https://github.com/Svalorzen/AI-Toolbox)
7. [MLPack](https://mlpack.org/)
8. [GoogleTest](https://github.com/google/googletest/tree/main/googletest)