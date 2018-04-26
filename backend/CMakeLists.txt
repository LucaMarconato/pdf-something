# TODO: this file must be fixed

# Build the backend library.
# add_subdirectory(database)

include_directories (../dependencies)
file (GLOB SOURCES ./*.cpp ./database/*.cpp ./io/*.cpp)
add_library (libbackend STATIC ${SOURCES} ${SOURCES_DATABASE})
target_include_directories (libbackend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
