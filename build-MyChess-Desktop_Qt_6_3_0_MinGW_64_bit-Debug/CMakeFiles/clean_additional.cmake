# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyChess_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyChess_autogen.dir\\ParseCache.txt"
  "MyChess_autogen"
  )
endif()
