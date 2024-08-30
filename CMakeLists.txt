cmake_minimum_required(VERSION 3.25)
project(Bless)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES "src/*.cpp")

# Add the library
if(WIN32)
    file(GLOB PLATFORM_SOURCES "src/windows/*.cpp")
elseif(UNIX)
    file(GLOB PLATFORM_SOURCES "src/linux/*.cpp")
endif()

add_library(Bless SHARED ${SOURCES} ${PLATFORM_SOURCES})

# Specify include directories
target_include_directories(Bless PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(Bless PUBLIC
	-Wall
)

# Add an executable
add_subdirectory(examples)

