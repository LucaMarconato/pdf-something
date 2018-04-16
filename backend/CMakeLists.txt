# Build the backend library.

file(GLOB SOURCES "./*.cpp")
add_library (libbackend STATIC ${SOURCES})
target_include_directories (libbackend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
