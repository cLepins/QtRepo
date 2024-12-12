# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DataBase_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DataBase_autogen.dir\\ParseCache.txt"
  "DataBase_autogen"
  )
endif()
