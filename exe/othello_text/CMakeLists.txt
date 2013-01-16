# Project configuration
project(othello_text)

# Include directories
include_directories(${ROOT_DIR}/lib/othello/include)

# Add executable
add_executable(othello_text
  src/main.cpp)
target_link_libraries(othello_text
  othello)
