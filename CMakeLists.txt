cmake_minimum_required(VERSION 3.17)
project(achacks)

set(CMAKE_CXX_STANDARD 20)
string(REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Remove RTTI to make it harder to RE

add_subdirectory(libgamehacks)

if (CMAKE_ARCH STREQUAL "x64")

else ()

    add_subdirectory(achacks)

endif ()
