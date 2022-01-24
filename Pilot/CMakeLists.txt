cmake_minimum_required(VERSION 3.14)

SET(PROJECT "Pilot")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(ENGINE_DIR ${SOURCE_DIR}/Engine)
set(ENGINE__IO_DIR ${ENGINE_DIR}/IO)
set(ENGINE__MATH_DIR ${ENGINE_DIR}/Maths)
set(ENGINE__PHYSICS_DIR ${ENGINE_DIR}/Physics)
set(GRAPHICS_DIR ${SOURCE_DIR}/Graphics)

include_directories(${SOURCE_DIR})
include_directories(${ENGINE_DIR})
include_directories(${ENGINE__IO_DIR})
include_directories(${ENGINE__MATH_DIR})
include_directories(${ENGINE__PHYSICS_DIR})
include_directories(${GRAPHICS_DIR})

file(GLOB SRCS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cpp")
file(GLOB ENGINE "${ENGINE_DIR}/*.h" "${ENGINE_DIR}/*.hpp" "${ENGINE_DIR}/*.cpp")
file(GLOB ENGINE__IO "${ENGINE__IO_DIR}/*.h" "${ENGINE__IO_DIR}/*.hpp" "${ENGINE__IO_DIR}/*.cpp")
file(GLOB ENGINE__Maths "${ENGINE__MATH_DIR}/*.h" "${ENGINE__MATH_DIR}/*.hpp" "${ENGINE__MATH_DIR}/*.cpp")
file(GLOB ENGINE__Physics "${ENGINE__PHYSICS_DIR}/*.h" "${ENGINE__PHYSICS_DIR}/*.hpp" "${ENGINE__PHYSICS_DIR}/*.cpp")
file(GLOB GRAPHICS "${GRAPHICS_DIR}/*.h" "${GRAPHICS_DIR}/*.hpp" "${GRAPHICS_DIR}/*.cpp")

source_group("" FILES ${SRCS})
source_group("Engine" FILES ${ENGINE})
source_group("Engine/IO" FILES ${ENGINE__IO})
source_group("Engine/Maths" FILES ${ENGINE__Maths})
source_group("Engine/Physics" FILES ${ENGINE__Physics})
source_group("Graphics" FILES ${GRAPHICS})

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cc" "${SOURCE_DIR}/*.cpp")

add_executable( ${PROJECT} ${SOURCES} )

set(GLFW_DIR "F:/Varun/Varun_Work/Libs/GLFW_3.3.6")
set(SOIL_DIR "F:/Varun/Varun_Work/Libs/SOIL")
set(WINDOWS_DIR "C:/Windows/System32")

include_directories(${GLFW_DIR}/include)
include_directories(${SOIL_DIR}/include)

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	find_library(GLFW_LIBRARY_D glfw3 HINTS ${GLFW_DIR}/lib/x64/vc2019)
	find_library(SOIL_LIBRARY_D soil-d HINTS ${SOIL_DIR}/lib/x64)
	
	find_library(GLFW_LIBRARY_R glfw3 HINTS ${GLFW_DIR}/lib/x64/vc2019)
	find_library(SOIL_LIBRARY_R soil HINTS ${SOIL_DIR}/lib/x64)
else ()
	find_library(GLFW_LIBRARY_D glfw3 HINTS ${GLFW_DIR}/lib/x86/vc2019)
	find_library(SOIL_LIBRARY_D soil-d HINTS ${SOIL_DIR}/lib/x86)
	
	find_library(GLFW_LIBRARY_R glfw3 HINTS ${GLFW_DIR}/lib/x86/vc2019)
	find_library(SOIL_LIBRARY_R soil HINTS ${SOIL_DIR}/lib/x86)
endif ()

target_link_libraries(${PROJECT} PUBLIC opengl32)
target_link_libraries(${PROJECT} PUBLIC debug ${GLFW_LIBRARY_D} optimized ${GLFW_LIBRARY_R})
target_link_libraries(${PROJECT} PUBLIC debug ${SOIL_LIBRARY_D} optimized ${SOIL_LIBRARY_R})

#set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")			# Project->Properties->Debugging->Environment
#set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "F:/config.txt")	# Project->Properties->Debugging->CommandArguments
#set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS "/VERBOSE:LIB")						# Project->Properties->Linker->CommandLine

set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:library")
 
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION})
