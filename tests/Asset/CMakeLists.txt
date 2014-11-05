# Asset - S3DR asset library tests
# ================================

PROJECT(test_AssetLib)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_SEARCH_MODULE(GLFW REQUIRED glfw3)
PKG_SEARCH_MODULE(ASSIMP REQUIRED assimp>=3.0)

# ==========================
# Asset tests
# ==========================
# Set source variables
SET(ASSET_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

SET(ASSET_TEST_SRC ${ASSET_TESTS_SRC_DIR}/main.cpp)

SET(ASSET_TEST_SRC_ALL ${ASSET_TEST_SRC})

# Set include directories
SET(ASSET_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${ASSET_TESTS_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Asset/lib/src)

# Build executabele
ADD_EXECUTABLE(test_AssetLib ${ASSET_TEST_SRC_ALL})
TARGET_LINK_LIBRARIES(test_AssetLib Asset)

