# Utility - utilty library
# ========================

# ========================
# Utility lib
# ========================
# Set source variables
SET(UTILITY_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

SET(UTILITY_LIB_SCR ${UTILITY_LIB_SRC_DIR}/utility/custom_operators.cpp  
					${UTILITY_LIB_SRC_DIR}/utility/math_utils.cpp
					${UTILITY_LIB_SRC_DIR}/utility/subject.cpp)

SET(S3DR_LIB_SRC_ALL ${UTILITY_LIB_SCR})

# Set include directories
SET(UTILITY_LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

INCLUDE_DIRECTORIES(${UTILITY_LIB_INC_DIR})

# Build library
ADD_LIBRARY(Utility STATIC ${S3DR_LIB_SRC_ALL})

# ========================
# Utility tests
# ========================
# Set source variables
SET(UTILITY_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/tests)

SET(UTILITY_TEST_SRC ${UTILITY_TESTS_SRC_DIR}/main.cpp)

SET(UTILITY_TEST_SRC_ALL ${UTILITY_TEST_SRC})

# Set include directories
SET(UTILITY_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/tests)

INCLUDE_DIRECTORIES(${UTILITY_TESTS_INC_DIR})

# Build executabele
ADD_EXECUTABLE(UTILIT_TESTS ${UTILITY_TEST_SRC_ALL})

TARGET_LINK_LIBRARIES(UTILIT_TESTS Utility)
