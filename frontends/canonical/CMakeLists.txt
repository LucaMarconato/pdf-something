# Build instruction for the canonical frontend.

file(GLOB SOURCES "./*.cpp")
add_executable(canonical-frontend ${SOURCES})
target_link_libraries(canonical-frontend LINK_PUBLIC libbackend)
