# Build instruction for the canonical frontend.
# add_subdirectory(backend_implementations)
include_directories (../../dependencies)
file(GLOB SOURCES "./*.cpp")
file(GLOB SOURCES_BACKEND_IMPLEMENTATION "./backend_implementations/*.cpp")
file(GLOB SOURCES_BACKEND_IMPLEMENTATION_IO "./backend_implementations/io/*.cpp")
add_executable(canonical-frontend ${SOURCES} ${SOURCES_BACKEND_IMPLEMENTATION} ${SOURCES_BACKEND_IMPLEMENTATION_IO})
target_link_libraries(canonical-frontend LINK_PUBLIC libbackend)
add_custom_target (run ./canonical-frontend > output.html && bash put_into_html_body.sh output.html)
