# Project configuration
project(othello)

# Include directories
include_directories(include)

# Add library
add_library(othello
  src/othello.cpp)

# Add test
add_executable(test_othello
  test/test_othello.cpp)
target_link_libraries(test_othello
  othello dl)
add_test(othello
  ${EXECUTABLE_OUTPUT_PATH}/test_othello)
