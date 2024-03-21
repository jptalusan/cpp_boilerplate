cmake_minimum_required(VERSION 3.14)

set(PROGRAM_NAME "my_program")

# Set the project name and version
project(${PROGRAM_NAME} VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


# For GoogleTest test cases
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# If used, then it will apply to all.
# add_definitions(
#     -Wall
#     -Wextra
#     -O2
#     # Other flags
# )

# Set default cmake build type to release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are:
          Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

# For additional Find library scripts
set(CUSTOM_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CUSTOM_MODULE_PATH})
# set(MLPACK_LIBRARIES ${MLPACK_LIBRARIES} ${OpenMP_CXX_LIBRARIES})

# Add MLPack since i built it myself.
set(MLPACK_INCLUDE_DIR "/home/jpt/libs/mlpack-4.3.0/mlpack-bin/include")
# Add SYSTEM keyword to silence warnings
include_directories(SYSTEM ${MLPACK_INCLUDE_DIR})

# Add GitHash
include(${CUSTOM_MODULE_PATH}/GitHash.cmake)
SetupGitHash()

# Add AIToolbox dependencies
find_package(Boost 1.53 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(EIGEN3_INCLUDE_DIR "/home/jpt/libs/eigen-3.4.0")
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(LpSolve REQUIRED)
include_directories(${LPSOLVE_INCLUDE_DIR})

# Add AIToolBox include dir
set(AITOOLBOX_INCLUDE_DIR "/home/jpt/git/AI-Toolbox/include")
include_directories(${AITOOLBOX_INCLUDE_DIR})

# Adding OpenMP
find_package(OpenMP REQUIRED)
find_package(Armadillo REQUIRED)

include_directories(${ARMADILLO_INCLUDE_DIRS})

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external_include)

# Add more include directories as needed

# from AI toolbox cmake.
# set(DEPENDENCIES "")
# function (AddDependency name)
#     set(DEPENDENCIES ${DEPENDENCIES} ${name} PARENT_SCOPE)
# endfunction (AddDependency)
# AddDependency(AI-Toolbox)

# Include the test subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)

# Add all source files
file(GLOB SOURCES "src/*.cpp")
# Add the executable
add_executable(${PROGRAM_NAME} ${SOURCES})


# Linking OpenMP
target_link_libraries(${PROGRAM_NAME} PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(${PROGRAM_NAME} PRIVATE ${ARMADILLO_LIBRARIES})
target_link_libraries(${PROGRAM_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROGRAM_NAME} PRIVATE ${BLAS_LIBRARIES})

# If using prebuilt apt install ones.
# target_link_libraries(${PROGRAM_NAME} PRIVATE mlpack)

# Adding built AI-Toolbox Libraries
add_library(MyExternalLib STATIC IMPORTED)
set_target_properties(MyExternalLib PROPERTIES IMPORTED_LOCATION "/home/jpt/git/AI-Toolbox/build/libAIToolboxMDP.a")
target_link_libraries(${PROGRAM_NAME} PRIVATE MyExternalLib)

add_library(MyExternalLib1 STATIC IMPORTED)
set_target_properties(MyExternalLib1 PROPERTIES IMPORTED_LOCATION "/home/jpt/git/AI-Toolbox/build/libAIToolboxPOMDP.a")
target_link_libraries(${PROGRAM_NAME} PRIVATE MyExternalLib1)

add_library(MyExternalLib2 STATIC IMPORTED)
set_target_properties(MyExternalLib2 PROPERTIES IMPORTED_LOCATION "/home/jpt/git/AI-Toolbox/build/libAIToolboxFMDP.a")
target_link_libraries(${PROGRAM_NAME} PRIVATE MyExternalLib2)

# For githash
target_link_libraries(${PROGRAM_NAME} PRIVATE ${GITHASH_LIBRARIES})

# Added this only to the program being build.
target_compile_options(${PROGRAM_NAME} PRIVATE 
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

# Set different compile definitions and options for debug and release builds
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROGRAM_NAME} PRIVATE DEBUG=1)
    target_compile_options(${PROGRAM_NAME} PRIVATE -g)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(${PROGRAM_NAME} PRIVATE NDEBUG=1)
    target_compile_options(${PROGRAM_NAME} PRIVATE -O2 -DNDEBUG)
endif()

# Specify the directories where the executable should be installed
install(TARGETS ${PROGRAM_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/binaries)