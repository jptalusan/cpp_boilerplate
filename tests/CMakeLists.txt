enable_testing()


# Needed to be able to reference external headers.
set(files
    ${PROJECT_SOURCE_DIR}/include/foo.h 
    ${PROJECT_SOURCE_DIR}/src/foo.cpp 
    ${PROJECT_SOURCE_DIR}/include/sample2.h 
    ${PROJECT_SOURCE_DIR}/src/sample2.cpp 
    )

add_executable(
  hello_test
  hello_test.cpp
  ${files}
)

target_link_libraries(
  hello_test
  GTest::gtest_main
)

# target_include_directories(hello_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(hello_test)