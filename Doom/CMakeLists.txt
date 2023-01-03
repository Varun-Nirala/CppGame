cmake_minimum_required(VERSION 3.14)

SET(PROJECT "Doom")

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

set(COMMON_LIBS_DIR "CommonLibs")
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/SDL2)
set(SDL2_IMAGE_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/SDL2_image)
set(SDL2_TTF_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/SDL_ttf)
set(SDL2_MIXER_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/SDL2_mixer)
set(GLM_DIR ${CMAKE_SOURCE_DIR}/../${COMMON_LIBS_DIR}/GLM/glm)

include_directories(${SDL2_DIR}/include)
include_directories(${SDL2_IMAGE_DIR}/include)
include_directories(${SDL2_TTF_DIR}/include)
include_directories(${SDL2_MIXER_DIR}/include)
include_directories(${GLM_DIR})

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x64/SDL2.lib")
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x64/SDL2main.lib")
	list(APPEND SDL2_LIB "${SDL2_IMAGE_DIR}/lib/x64/SDL2_image.lib")
	list(APPEND SDL2_LIB "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.lib")
	list(APPEND SDL2_LIB "${SDL2_MIXER_DIR}/lib/x64/SDL2_mixer.lib")
	set(MY_PATH "PATH=%PATH%" "${SDL2_DIR}/lib/x64;${SDL2_IMAGE_DIR}/lib/x64;${SDL2_TTF_DIR}/lib/x64;${SDL2_MIXER_DIR}/lib/x64")
else ()
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x86/SDL2.lib")
	list(APPEND SDL2_LIB "${SDL2_DIR}/lib/x86/SDL2main.lib")
	list(APPEND SDL2_LIB "${SDL2_IMAGE_DIR}/lib/x86/SDL2_image.lib")
	list(APPEND SDL2_LIB "${SDL2_TTF_DIR}/lib/x86/SDL2_ttf.lib")
	list(APPEND SDL2_LIB "${SDL2_MIXER_DIR}/lib/x86/SDL2_mixer.lib")
	set(MY_PATH "PATH=%PATH%" "${SDL2_DIR}/lib/x86;${SDL2_IMAGE_DIR}/lib/x86;${SDL2_TTF_DIR}/lib/x86;${SDL2_MIXER_DIR}/lib/x86")
endif ()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(COMMON_DIR ${SOURCE_DIR}/common)

include_directories(${SOURCE_DIR})

file(GLOB SRCS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cpp")
file(GLOB COMMON "${COMMON_DIR}/*.h" "${COMMON_DIR}/*.hpp" "${COMMON_DIR}/*.cpp")

source_group("" FILES ${SRCS})
source_group("common" FILES ${COMMON})

# CONFIGURE_DEPENDS  to automatically fetch new file without need of manually runing cmake again
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS  "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cc" "${SOURCE_DIR}/*.cpp")

add_executable( ${PROJECT} ${SOURCES} )

target_link_libraries(${PROJECT} ${SDL2_LIB})

set_target_properties(${PROJECT} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT})
#Extra step to copy resources
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION})