# Project configuration
project(engines)

# Include directories
include_directories(${ROOT_DIR}/lib/othello/include)

# Add shared library (plugin)
add_library(maxchips SHARED
  src/engine_maxchips.cpp)

# Set properties and install
set_target_properties(maxchips
  PROPERTIES PREFIX "" SUFFIX ".eng")
install(TARGETS maxchips
  LIBRARY DESTINATION ${ROOT_DIR}/bin)
  