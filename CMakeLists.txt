cmake_minimum_required(VERSION 3.20)

project(memo-pad-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(memo-pad-cpp
    src/main.cpp
    src/ui/text.cpp
    src/ui/button.cpp
)

target_compile_options(memo-pad-cpp PRIVATE
    -Wall
    -Wextra
)

target_include_directories(memo-pad-cpp PRIVATE
    include
)

target_link_libraries(memo-pad-cpp PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)

set_target_properties(memo-pad-cpp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS memo-pad-cpp DESTINATION bin)
