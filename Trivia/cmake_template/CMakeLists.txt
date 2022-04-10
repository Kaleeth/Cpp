cmake_minimum_required (VERSION 3.16 FATAL)
set (CMAKE_CXX_STANDARD 20)

project (cmake_template)
set (TARGET_NAME cmake_tmpl)

# PCL is an example library
find_package (PCL 1.2 REQUIRED)

include_directories (${PCL_INCLUDE_DIRS})

# you may prefer to separate sources and headers
add_executable (TARGET_NAME Local.cpp part.h grab.h interface.h test.cpp test.h)

target_link_libraries (TARGET_NAME PRIVATE ${PCL_LIBRARIES})