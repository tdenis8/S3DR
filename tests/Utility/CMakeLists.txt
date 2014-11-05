# Utility - S3DR utilty library tests
# ===================================

PROJECT(test_UtilityLib)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# =============================
# Utility tests
# =============================
# Set source variables
SET(UTILITY_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

SET(UTILITY_TEST_SRC ${UTILITY_TESTS_SRC_DIR}/main.cpp
					 ${UTILITY_TESTS_SRC_DIR}/subject_tests.cpp)

SET(UTILITY_TEST_SRC_ALL ${UTILITY_TEST_SRC})

# Set include directories
SET(UTILITY_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${UTILITY_TESTS_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Utility/lib/src)

# Build executabele
ADD_EXECUTABLE(test_UtilityLib ${UTILITY_TEST_SRC_ALL})

TARGET_LINK_LIBRARIES(test_UtilityLib Utility)
