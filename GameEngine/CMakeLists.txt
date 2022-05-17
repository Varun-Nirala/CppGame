cmake_minimum_required(VERSION 3.14)

SET(PROJECT "GameEngine")

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
project( ${PROJECT} VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(SDL2_DIR ${CMAKE_SOURCE_DIR}/Externals/SDL2)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/Externals/GLAD)
set(GLEW_DIR ${CMAKE_SOURCE_DIR}/Externals/GLEW)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/Externals/GLFW)
set(WINDOWS_DIR "C:/Windows/System32")

file(GLOB SOURCES "src/*.cpp" "src/*.h" "src/*.c")

include_directories(${SDL2_DIR}/include)
include_directories(${GLAD_DIR}/include)
include_directories(${GLEW_DIR}/include)
include_directories(${GLFW_DIR}/include)

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x64/SDL2.lib")
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x64/SDL2main.lib")
	list(APPEND GLEW_LIB "${GLEW_DIR}/lib/x64/glew32.lib")
	list(APPEND GLFW_LIB "${GLFW_DIR}/lib/x64/vc2019/glfw3.lib")
	
	set(MY_PATH "PATH=%PATH%" "${SDL2_DIR}/lib/x64;${GLEW_DIR}/lib/x64;${GLFW_DIR}/lib/x64/vc2019")
else ()
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x86/SDL2.lib")
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x86/SDL2main.lib")
	list(APPEND GLEW_LIB "${GLEW_DIR}/lib/x86/glew32.lib")
	list(APPEND GLFW_LIB "${GLFW_DIR}/lib/x86/vc2019/glfw3.lib")
	
	set(MY_PATH "PATH=%PATH%" "${SDL2_DIR}/lib/x86;${GLEW_DIR}/lib/x86;${GLFW_DIR}/lib/x86/vc2019")
endif ()
add_library(glad ${GLAD_DIR}/src/glad.c)

add_executable( ${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT} opengl32 glad)
target_link_libraries(${PROJECT} ${SDL2_LIB})
target_link_libraries(${PROJECT} ${GLEW_LIB})
target_link_libraries(${PROJECT} ${GLFW_LIB})

set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:library")
set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")
 
#file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION})
