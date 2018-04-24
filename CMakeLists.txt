# Build system config.

cmake_minimum_required (VERSION 2.6)
project (pdf-something)
# add_definitions("-std=c++17 -Wall -g -O0")
add_definitions("-std=c++17 -O2")

# Version Number

set (VERSION_MAJOR 0)
set (VERSION_MINOR 0)
set (VERSION_RELEASE 0)
set (VERSION_BUILD 0)

# Recur on subfolders

add_subdirectory (backend)
add_subdirectory (frontends)
#add_subdirectory (tests)

