file(GLOB_RECURSE TEST_FILES *.cc)

add_executable(tests ${TEST_FILES})

set_target_properties(tests PROPERTIES
  CXX_STANDARD 17
)

target_include_directories(tests PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(tests gtest_main gmock oozrt)

add_test(
  NAME all
  COMMAND ${CMAKE_BINARY_DIR}/test/tests
)
