cmake_minimum_required(VERSION 3.14)

SET(PROJECT "ParticleSimulator2D")

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

# Common libs START

set(COMMON_LIBS_DIR "CommonLibs")
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/GLAD)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/GLFW)
set(GLM_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/GLM/glm)
set(FREETYPE_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/FREE_TYPE)

set(WINDOWS_DIR "C:/Windows/System32")

include_directories(${GLAD_DIR}/include)
include_directories(${GLFW_DIR}/include)
include_directories(${GLM_DIR})
include_directories(${FREETYPE_DIR}/include)

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	list(APPEND GLFW_LIB "${GLFW_DIR}/lib/x64/glfw3.lib")
	list(APPEND FREETYPE_LIB "${FREETYPE_DIR}/lib/x64/freetype.lib")
	set(MY_PATH "PATH=%PATH%" "${GLFW_DIR}/lib/x64;${SDL2_DIR}/lib/x64;${FREETYPE_DIR}/lib/x64")
else ()
	list(APPEND GLFW_LIB "${GLFW_DIR}/lib/x86/glfw3.lib")
	list(APPEND FREETYPE_LIB "${FREETYPE_DIR}/lib/x86/freetype.lib")
	set(MY_PATH "PATH=%PATH%" "${GLFW_DIR}/lib/x86;${SDL2_DIR}/lib/x86${FREETYPE_DIR}/lib/x86")
endif ()

#add_library(glad ${GLAD_DIR}/src/glad.c)
#add_library(stb_image ${STB_IMG_DIR}/stb_image.cpp)
# Common libs END

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(COMMON_DIR ${SOURCE_DIR}/Common)

include_directories(${SOURCE_DIR})

file(GLOB SRCS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cpp")
file(GLOB COMMON "${COMMON_DIR}/*.h" "${COMMON_DIR}/*.hpp" "${COMMON_DIR}/*.cpp")

source_group("" FILES ${SRCS})
source_group("Common" FILES ${COMMON})

# CONFIGURE_DEPENDS  to automatically fetch new file without need of manually runing cmake again
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS  "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cc" "${SOURCE_DIR}/*.cpp")

set(GLAD_SRC ${GLAD_DIR}/src/glad.c)
add_executable( ${PROJECT} ${SOURCES} ${GLAD_SRC})

target_link_libraries(${PROJECT} opengl32) # glad stb_image)
target_link_libraries(${PROJECT} ${GLFW_LIB} ${FREETYPE_LIB})

set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION})
