cmake_minimum_required(VERSION 3.14)

SET(PROJECT "Pilot")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine)
include_directories(${CMAKE_SOURCE_DIR}/src/Graphics)
file(GLOB SOURCES "src/Engine/*.cpp" "src/Graphics/*.cpp" "src/*.cpp")

add_executable( ${PROJECT} ${SOURCES} )

set(GLFW_DIR "F:/Varun/Varun_Work/Libs/GLFW_3.3.6")
set(SOIL_DIR "F:/Varun/Varun_Work/Libs/SOIL.1.16.0")
set(WINDOWS_DIR "C:/Windows/System32")

include_directories(${GLFW_DIR}/include)
include_directories(${SOIL_DIR}/include)

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	list(APPEND ALL_LIBS "${GLFW_DIR}/lib/x64/vc2019/glfw3.lib")
	list(APPEND ALL_LIBS "${SOIL_DIR}/lib/x64/soil.lib")
	set(MY_PATH "PATH=%PATH%" "${GLFW_DIR}/lib/x64/vc2019;${SOIL_DIR}/lib/x64")
else ()
	list(APPEND ALL_LIBS "${GLFW_DIR}/lib/x86/vc2019/glfw3.lib")
	list(APPEND ALL_LIBS "${SOIL_DIR}/lib/x86/soil.lib")
	set(MY_PATH "PATH=%PATH%" "${GLFW_DIR}/lib/x86/vc2019;${SOIL_DIR}/lib/x86")
endif ()

target_link_libraries(${PROJECT} ${ALL_LIBS})

set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION})
