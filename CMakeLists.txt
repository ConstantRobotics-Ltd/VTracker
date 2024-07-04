cmake_minimum_required(VERSION 3.13)



################################################################################
## PROJECT
## name and version
################################################################################
project(VTracker LANGUAGES CXX)



################################################################################
## SETTINGS
## basic project settings before use
################################################################################
# If this project is used as a submodule, the variable should be overridden
# to "OFF" in the top-level application (to disable forced cache rewriting)
option(${PARENT}_SUBMODULE_CACHE_OVERWRITE "Enable forced cache rewriting" ON)
if (${PARENT}_SUBMODULE_CACHE_OVERWRITE)
    SET(REWRITE_FORCE "FORCE")
else()
    SET(REWRITE_FORCE "")
endif()



################################################################################
## CONFIGURATION
## project configuration
################################################################################
SET(${PARENT}_VTRACKER                       ON  CACHE BOOL "" ${REWRITE_FORCE})
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    SET(${PARENT}_VTRACKER_TEST              OFF CACHE BOOL "" ${REWRITE_FORCE})
    SET(${PARENT}_VTRACKER_EXAMPLE           OFF CACHE BOOL "" ${REWRITE_FORCE})
    message("Included as subrepository")
else()
    SET(${PARENT}_VTRACKER_TEST              ON  CACHE BOOL "" ${REWRITE_FORCE})
    SET(${PARENT}_VTRACKER_EXAMPLE           ON  CACHE BOOL "" ${REWRITE_FORCE})
    message("Stand alone repository")
endif()



################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the project configuration
################################################################################
if (${PARENT}_VTRACKER)
    add_subdirectory(3rdparty)
    add_subdirectory(src)
endif()

if (${PARENT}_VTRACKER_TEST)
    add_subdirectory(test)
endif()

if (${PARENT}_VTRACKER_EXAMPLE)
    add_subdirectory(example)
endif()
