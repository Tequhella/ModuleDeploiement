# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Find the gtkmm package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

if(GTKMM_FOUND)
    include_directories(${GTKMM_INCLUDE_DIRS})
    link_directories(${GTKMM_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "GTKMM not found")
endif()

include_directories(${GTKMM_INCLUDE_DIRS})

# Add executable for your main code
add_executable(MyApp main.cpp Age.cpp Form.cpp)

# Add executable for your tests
add_executable(MyTests test_Age.cpp test_Form.cpp)

# Link gtkmm libraries to the main executable
target_link_libraries(MyApp ${GTKMM_LIBRARIES})

# Link Boost libraries to the test executable
target_link_libraries(MyTests PRIVATE Boost::unit_test_framework ${GTKMM_LIBRARIES})

# Add a custom target to run the tests
add_custom_target(run_tests COMMAND MyTests)

# Set the working directory for running tests
set_property(TARGET run_tests PROPERTY WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Add a test target to run the tests using CTest
add_test(NAME MyTests COMMAND MyTests)

# Add gcov compiler and linker flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Add a custom target to run gcov
add_custom_target(coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} run_tests
    COMMAND mkdir -p coverage
    COMMAND gcov -o ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/MyTests.dir/ test_Age.cpp.gcno test_Form.cpp.gcno
    COMMAND mv *.gcov coverage/
    COMMAND gcovr -e test_Age.cpp -e test_Form.cpp -e main.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    #DEPENDS run_tests
)