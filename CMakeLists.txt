cmake_minimum_required(VERSION 3.4.1)
option(ENABLE_SKOTTIE "Enable skia." OFF)
option(ENABLE_VIEWER "Enable skia." OFF)
option(ENABLE_EDITOR "Enable skia." OFF)
option(ENABLE_SKQP "Enable skia." OFF)
#//:executable
option(ENABLE_EXECUTABLE "Enable executable." OFF)

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_SKIA "${SRC_ROOT}/skia")

# Detect CPU type and whether we're building 64-bit or 32-bit code
math(EXPR BITS "${CMAKE_SIZEOF_VOID_P} * 8")
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} CMAKE_SYSTEM_PROCESSOR_LC)
if(CMAKE_SYSTEM_PROCESSOR_LC MATCHES "x86_64" OR
        CMAKE_SYSTEM_PROCESSOR_LC MATCHES "amd64" OR
        CMAKE_SYSTEM_PROCESSOR_LC MATCHES "i[0-9]86" OR
        CMAKE_SYSTEM_PROCESSOR_LC MATCHES "x86" OR
        CMAKE_SYSTEM_PROCESSOR_LC MATCHES "ia32")
    if(BITS EQUAL 64)
        set(CPU_TYPE x86_64)
    else()
        set(CPU_TYPE i386)
    endif()
    if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL ${CPU_TYPE})
        set(CMAKE_SYSTEM_PROCESSOR ${CPU_TYPE})
    endif()
elseif(CMAKE_SYSTEM_PROCESSOR_LC STREQUAL "aarch64" OR
        CMAKE_SYSTEM_PROCESSOR_LC MATCHES "arm*64*")
    set(CPU_TYPE arm64)
elseif(CMAKE_SYSTEM_PROCESSOR_LC MATCHES "arm*")
    set(CPU_TYPE arm)
elseif(CMAKE_SYSTEM_PROCESSOR_LC MATCHES "ppc*" OR
        CMAKE_SYSTEM_PROCESSOR_LC MATCHES "powerpc*")
    set(CPU_TYPE powerpc)
else()
    set(CPU_TYPE ${CMAKE_SYSTEM_PROCESSOR_LC})
endif()
message(STATUS "${BITS}-bit build (${CPU_TYPE})")

add_subdirectory(${SRC_SKIA}/cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp)