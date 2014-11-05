# Utility - S3DR utilty library
# =============================

PROJECT(Utility)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# =============================
# Utility lib
# =============================
# Set source variables
SET(UTILITY_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

SET(UTILITY_LIB_SRC ${UTILITY_LIB_SRC_DIR}/utility/custom_operators.cpp  
					${UTILITY_LIB_SRC_DIR}/utility/math_utils.cpp
					${UTILITY_LIB_SRC_DIR}/utility/subject.cpp)

SET(UTILITY_LIB_SRC_ALL ${UTILITY_LIB_SRC})

# Set include directories
SET(UTILITY_LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

INCLUDE_DIRECTORIES(${UTILITY_LIB_INC_DIR})

# Build library
ADD_LIBRARY(Utility STATIC ${UTILITY_LIB_SRC_ALL})
