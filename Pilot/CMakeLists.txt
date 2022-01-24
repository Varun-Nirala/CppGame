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

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine/IO)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine/Maths)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine/Physics)
include_directories(${CMAKE_SOURCE_DIR}/src/Graphics)

file(GLOB SOURCES "src/Engine/*.cpp" "src/Engine/IO/*.cpp" "src/Engine/Maths/*.cpp" "src/Engine/Physics/*.cpp" "src/Graphics/*.cpp" "src/*.cpp" "src/Engine/*.h" "src/Engine/IO/*.h" "src/Engine/Maths/*.h" "src/Engine/Physics/*.h" "src/Graphics/*.h" "src/*.h")

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
