# Utility - S3DR utilty library
# =============================

PROJECT(Utility)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# =============================
# Utility lib
# =============================
# Set source variables
SET(UTILITY_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

SET(UTILITY_LIB_SCR ${UTILITY_LIB_SRC_DIR}/utility/custom_operators.cpp  
					${UTILITY_LIB_SRC_DIR}/utility/math_utils.cpp
					${UTILITY_LIB_SRC_DIR}/utility/subject.cpp)

SET(UTILITY_LIB_SRC_ALL ${UTILITY_LIB_SCR})

# Set include directories
SET(UTILITY_LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES(${UTILITY_LIB_INC_DIR})

# Build library
ADD_LIBRARY(Utility STATIC ${UTILITY_LIB_SRC_ALL})

# =============================
# Utility tests
# =============================
# Set source variables
SET(UTILITY_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

SET(UTILITY_TEST_SRC ${UTILITY_TESTS_SRC_DIR}/main.cpp)

SET(UTILITY_TEST_SRC_ALL ${UTILITY_TEST_SRC})

# Set include directories
SET(UTILITY_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

INCLUDE_DIRECTORIES(${UTILITY_TESTS_INC_DIR})

# Build executabele
ADD_EXECUTABLE(UTILITY_TESTS ${UTILITY_TEST_SRC_ALL})

TARGET_LINK_LIBRARIES(UTILITY_TESTS Utility)
