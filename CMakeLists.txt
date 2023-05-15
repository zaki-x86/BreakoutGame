cmake_minimum_required(VERSION 3.16)

project(
    "Breakout"
    VERSION 0.1
    DESCRIPTION "Breakout game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE EXT_SOURCES external/*cpp)

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${EXT_SOURCES}
)


target_include_directories(${PROJECT_NAME} PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        external
        test
)

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
)

# Store the executable in bin/ folder
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Tell CMake to copy all shaders and assets to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# If debug, send -DDEBUG to the compiler
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG ggdb3 EXCEPTIONS_ENABLED)
endif()

message(STATUS "Building tests ...")
add_subdirectory(test)