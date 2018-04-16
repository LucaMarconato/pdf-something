# Build instruction for the canonical frontend.
add_subdirectory(backend_implementations)
file(GLOB SOURCES "./*.cpp")
file(GLOB SOURCES_BACKEND_IMPLEMENTATION "./backend_implementations/*.cpp")
add_executable(canonical-frontend ${SOURCES} ${SOURCES_BACKEND_IMPLEMENTATION})
target_link_libraries(canonical-frontend LINK_PUBLIC libbackend)
