# Project configuration
project(othello)

# Include directories
include_directories(include)

# Add library
if (${ARCH} STREQUAL "x86_64")
  add_library(othello
    src/othello.cpp
    src/lut64.cpp)
else ()
  add_library(othello
    src/othello.cpp
    src/lut.cpp)
endif ()

# Add test
add_executable(test_othello
  test/test_othello.cpp)
target_link_libraries(test_othello
  othello dl)
add_test(othello
  ${EXECUTABLE_OUTPUT_PATH}/test_othello)
