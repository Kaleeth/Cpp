set(SOURCE main_file.cpp another_file.cpp)

add_executable(${CMAKE_PROJECT_NAME}.out ${SOURCE})

target_include_directories(${CMAKE_PROJECT_NAME}.out PRIVATE headers)