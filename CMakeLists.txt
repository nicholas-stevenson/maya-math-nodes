# Copyright (c) 2018-2021 Serguei Kalentchouk et al. All rights reserved.
# Use of this source code is governed by an MIT license that can be found in the LICENSE file.

# Define project
cmake_minimum_required(VERSION 3.3)
project(maya-math-nodes VERSION 1.6.0)

include(CMakePrintHelpers)

# Set project version macro
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")

# Set default Maya version
set(MAYA_VERSION 2023)

# Set node name prefix macro
set(NODE_NAME_PREFIX "math_")

add_definitions(-DNODE_NAME_PREFIX="${NODE_NAME_PREFIX}")

# Set compile flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_compile_options(/wd4068 /EHsc)
endif()

include_directories("${CMAKE_SOURCE_DIR}/../../../../shared/resources/maya/2023/devkit/include")
link_directories("${CMAKE_SOURCE_DIR}/../../../../shared/resources/maya/2023/devkit/lib")

# Create target
add_library(mayaMathNodes SHARED
    src/Absolute.h
    src/Add.h
    src/Array.h
    src/Condition.h
    src/Clamp.h
    src/Debug.h
    src/Distance.h
    src/Divide.h
    src/Convert.h
    src/Interpolate.h
    src/Inverse.h
    src/MinMax.h
    src/Multiply.h
    src/Negate.h
    src/Plugin.cpp
    src/Power.h
    src/Round.h
    src/Trig.h
    src/Twist.h
    src/Subtract.h
    src/Utils.h
    src/VectorOps.h)

TARGET_LINK_LIBRARIES(mayaMathNodes Foundation.lib OpenMaya.lib OpenMayaAnim.lib OpenMayaUI.lib OpenMayaRender.lib)

SET_TARGET_PROPERTIES(mayaMathNodes PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plug-ins/${MAYA_VERSION}")
SET_TARGET_PROPERTIES(mayaMathNodes PROPERTIES OUTPUT_NAME mayaMathNodes)
SET_TARGET_PROPERTIES(mayaMathNodes PROPERTIES SUFFIX ".mll")
SET_TARGET_PROPERTIES(mayaMathNodes PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(mayaMathNodes PROPERTIES LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin")


# Set installation directory
if(NOT DEFINED INSTALL_DIR)
    set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/dist)
endif()

configure_file(MayaMathNodes.mod.in MayaMathNodes.mod)

install(TARGETS mayaMathNodes
    LIBRARY DESTINATION ${INSTALL_DIR}/MayaMathNodes/plug-ins/${MAYA_VERSION}
    RUNTIME DESTINATION ${INSTALL_DIR}/MayaMathNodes/plug-ins/${MAYA_VERSION})
install(DIRECTORY python/maya_math_nodes
    DESTINATION ${INSTALL_DIR}/MayaMathNodes/scripts
    PATTERN "*.pyc" EXCLUDE
    PATTERN ".*" EXCLUDE)
install(FILES ${CMAKE_BINARY_DIR}/MayaMathNodes.mod DESTINATION ${INSTALL_DIR})
