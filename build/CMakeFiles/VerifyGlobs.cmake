# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# cs225_sources at lib/CMakeLists.txt:12 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225FinalProject/graF/lib/cs225/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225FinalProject/graF/lib/cs225/HSLAPixel.cpp"
  "/workspaces/CS225FinalProject/graF/lib/cs225/PNG.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225FinalProject/graF/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225FinalProject/graF/lib/lodepng/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225FinalProject/graF/lib/lodepng/lodepng.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225FinalProject/graF/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225FinalProject/graF/lib/lodepng/*.h")
set(OLD_GLOB
  "/workspaces/CS225FinalProject/graF/lib/lodepng/lodepng.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225FinalProject/graF/build/CMakeFiles/cmake.verify_globs")
endif()

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225FinalProject/graF/src/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225FinalProject/graF/src/Image.cpp"
  "/workspaces/CS225FinalProject/graF/src/drawing.cpp"
  "/workspaces/CS225FinalProject/graF/src/graph.cpp"
  "/workspaces/CS225FinalProject/graF/src/utilities.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225FinalProject/graF/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:131 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225FinalProject/graF/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225FinalProject/graF/tests/tests-bfs.cpp"
  "/workspaces/CS225FinalProject/graF/tests/tests-dataparsing.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225FinalProject/graF/build/CMakeFiles/cmake.verify_globs")
endif()
