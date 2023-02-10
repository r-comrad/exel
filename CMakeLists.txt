#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.3)

project(Exel)

#--------------------------------------------------------------------------------

# OS detection
if (${MSVC})
    set(OS "BILL_WINDOWS")
else()
    set(OS "LINUS_LINUX")
endif()
message(-----> ${OS})

#--------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources include
add_executable(${PROJECT_NAME} main.cpp)

# Output file name settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .exe)

#--------------------------------------------------------------------------------
