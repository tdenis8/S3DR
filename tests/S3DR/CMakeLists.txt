# S3DR - Small 3D renderer lib tests
# ==================================

PROJECT(test_S3DRLib)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# ========================
# S3DR tests
# ========================
# Set source variables
SET(S3DR_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

SET(S3DR_MAIN_SRC ${S3DR_TESTS_SRC_DIR}/main.cpp)

SET(S3DR_AUXILIARY_SRC ${S3DR_TESTS_SRC_DIR}/auxiliary/resources_handler.cpp  
                  	   ${S3DR_TESTS_SRC_DIR}/auxiliary/test_env.cpp)

SET(S3DR_TESTS_SRC ${S3DR_TESTS_SRC_DIR}/tests/model_tests.cpp
                   ${S3DR_TESTS_SRC_DIR}/tests/point_tests.cpp   
                   ${S3DR_TESTS_SRC_DIR}/tests/line_tests.cpp   
                   ${S3DR_TESTS_SRC_DIR}/tests/shell_tests.cpp   
                   ${S3DR_TESTS_SRC_DIR}/tests/text_tests.cpp)

SET(S3DR_TESTS_SRC_ALL ${S3DR_MAIN_SRC}
					   ${S3DR_AUXILIARY_SRC}
					   ${S3DR_TESTS_SRC})

# Set include directories
SET(S3DR_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${S3DR_TESTS_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/S3DR/lib/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Asset/lib/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Utility/lib/src)

# Build executabele
ADD_EXECUTABLE(test_S3DRLib ${S3DR_TESTS_SRC_ALL})

TARGET_LINK_LIBRARIES(test_S3DRLib S3DR) 
TARGET_LINK_LIBRARIES(test_S3DRLib Asset)
TARGET_LINK_LIBRARIES(test_S3DRLib Utility)
