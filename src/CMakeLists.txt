cmake_minimum_required(VERSION 3.13)



################################################################################
## LIBRARY-PROJECT
## name and version
################################################################################
project(VTracker VERSION 1.4.6 LANGUAGES CXX)



################################################################################
## SETTINGS
## basic project settings before use
################################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Standard C++ only (no compiler extensions)
set(CMAKE_CXX_EXTENSIONS OFF)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
file (GLOB_RECURSE IN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h.in)
configure_file(${IN_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Version.h)



################################################################################
## TARGET
## create target and add include path
################################################################################
# create glob files for *.h, *.cpp, *.hpp
file (GLOB_RECURSE H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})
# create lib from src
if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} ${SOURCES})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



################################################################################
## LINK LIBRARIES
## linking all dependencies
################################################################################
target_link_libraries(${PROJECT_NAME} Frame)
target_link_libraries(${PROJECT_NAME} ConfigReader)

include(CheckCXXCompilerFlag)
if(MSVC)
    # All warnings (as errors), standard conformance, security checks, stack
    # cookies and control flow guard
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /permissive- /sdl /GS /guard:cf)
    # ASLR, DEP and control flow guard for a dynamic library
    target_link_options(${PROJECT_NAME} PRIVATE /DYNAMICBASE /NXCOMPAT /guard:cf)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wsign-conversion
        -Wold-style-cast -Wcast-qual -Wformat=2 -Wnon-virtual-dtor
        -Woverloaded-virtual -Wdouble-promotion -Wimplicit-fallthrough
        -Wmissing-declarations -Wundef -Wextra-semi
        -Wzero-as-null-pointer-constant)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -Wdocumentation)
    endif()
    if(NOT WIN32)
        # Stack protector and hardened libc calls (optimized builds only)
        target_compile_options(${PROJECT_NAME} PRIVATE -fstack-protector-strong
            "$<$<NOT:$<CONFIG:Debug>>:-U_FORTIFY_SOURCE;-D_FORTIFY_SOURCE=2>")
        # Stack clash protection and control flow protection (x86 CET or ARM
        # pointer authentication and branch target identification), if the
        # compiler supports them for the target
        set(HARDENING_FLAGS -fstack-clash-protection -fcf-protection=full)
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "^([Aa][Aa][Rr][Cc][Hh]64|[Aa][Rr][Mm])")
            # Clang on x86 accepts this option in the check but warns on every use
            list(APPEND HARDENING_FLAGS -mbranch-protection=standard)
        endif()
        foreach(FLAG ${HARDENING_FLAGS})
            string(MAKE_C_IDENTIFIER "HAS${FLAG}" FLAG_VAR)
            check_cxx_compiler_flag(${FLAG} ${FLAG_VAR})
            if(${FLAG_VAR})
                target_compile_options(${PROJECT_NAME} PRIVATE ${FLAG})
            endif()
        endforeach()
    endif()
    if(UNIX AND NOT APPLE)
        # Full RELRO and non-executable stack for a dynamic library
        target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,relro,-z,now,-z,noexecstack)
    endif()
endif()
