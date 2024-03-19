cmake_minimum_required(VERSION 3.10)

set(PROGRAM_NAME "my_program")

# Set the project name and version
project(${PROGRAM_NAME} VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external_include)
# Add more include directories as needed

# Add all source files
file(GLOB SOURCES "src/*.cpp")
# Add the executable
add_executable(${PROGRAM_NAME} ${SOURCES})

# Set different compile definitions and options for debug and release builds
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROGRAM_NAME} PRIVATE DEBUG=1)
    target_compile_options(${PROGRAM_NAME} PRIVATE -g)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(${PROGRAM_NAME} PRIVATE NDEBUG=1)
    target_compile_options(${PROGRAM_NAME} PRIVATE -O2)
endif()

# Specify the directories where the executable should be installed
install(TARGETS ${PROGRAM_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/binaries)