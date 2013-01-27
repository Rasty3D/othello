# Project configuration
project(othello_lut)

# Include directories
include_directories(${ROOT_DIR}/lib/othello/include)

# Add executable
add_executable(othello_lut
  src/main.cpp)