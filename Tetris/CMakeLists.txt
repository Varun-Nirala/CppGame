cmake_minimum_required(VERSION 3.14)

SET(PROJECT "Tetris")
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
file(GLOB SOURCES "src/*.cpp" "src/*.h")

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/../CommonLibs/SFML")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x64/sfml-system-d.lib" optimized "${SFML_DIR}/lib/x64/sfml-system.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x64/sfml-window-d.lib" optimized "${SFML_DIR}/lib/x64/sfml-window.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x64/sfml-graphics-d.lib" optimized "${SFML_DIR}/lib/x64/sfml-graphics.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x64/sfml-network-d.lib" optimized "${SFML_DIR}/lib/x64/sfml-network.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x64/sfml-audio-d.lib" optimized "${SFML_DIR}/lib/x64/sfml-audio.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x64/sfml-main-d.lib" optimized "${SFML_DIR}/lib/x64/sfml-main.lib")
	set(MY_PATH "PATH=%PATH%" "${SFML_DIR}/lib/x64")
else ()
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x86/sfml-system-d.lib" optimized "${SFML_DIR}/lib/x86/sfml-system.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x86/sfml-window-d.lib" optimized "${SFML_DIR}/lib/x86/sfml-window.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x86/sfml-graphics-d.lib" optimized "${SFML_DIR}/lib/x86/sfml-graphics.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x86/sfml-network-d.lib" optimized "${SFML_DIR}/lib/x86/sfml-network.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x86/sfml-audio-d.lib" optimized "${SFML_DIR}/lib/x86/sfml-audio.lib")
	list(APPEND SFML_LIB debug "${SFML_DIR}/lib/x86/sfml-main-d.lib" optimized "${SFML_DIR}/lib/x86/sfml-main.lib")
	set(MY_PATH "PATH=%PATH%" "${SFML_DIR}/lib/x86")
endif ()

include_directories(${SFML_DIR}/include)

add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT} ${SFML_LIB})

set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT})