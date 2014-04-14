# Asset - S3DR asset library
# ==========================

PROJECT(Asset)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# ==========================
# Asset lib
# ==========================
# Set source variables
SET(ASSET_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

SET(ASSET_LIB_SCR ${ASSET_LIB_SRC_DIR}/asset/3D_shapes.cpp  
				  ${ASSET_LIB_SRC_DIR}/asset/assimp_mesh_loader.cpp
				  ${ASSET_LIB_SRC_DIR}/asset/combined_operator.cpp
				  ${ASSET_LIB_SRC_DIR}/asset/open_gl_context.cpp
				  ${ASSET_LIB_SRC_DIR}/asset/view_window.cpp)

SET(ASSET_LIB_SRC_ALL ${ASSET_LIB_SCR})

# Set include directories
SET(ASSET_LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

INCLUDE_DIRECTORIES(${ASSET_LIB_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/S3DR/lib/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Utility/lib/src)

# Build library
ADD_LIBRARY(Asset STATIC ${ASSET_LIB_SRC_ALL})
TARGET_LINK_LIBRARIES(Asset Utility)
TARGET_LINK_LIBRARIES(Asset S3DR)
TARGET_LINK_LIBRARIES(Asset assimp
							glfw)
#ADD_DEPENDENCIES(Asset Utility)
#ADD_DEPENDENCIES(Asset S3DR)

# ==========================
# Asset tests
# ==========================
# Set source variables
SET(ASSET_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

SET(ASSET_TEST_SRC ${ASSET_TESTS_SRC_DIR}/main.cpp)

SET(ASSET_TEST_SRC_ALL ${ASSET_TEST_SRC})

# Set include directories
SET(ASSET_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

INCLUDE_DIRECTORIES(${ASSET_TESTS_INC_DIR})

# Build executabele
ADD_EXECUTABLE(ASSET_TESTS ${ASSET_TEST_SRC_ALL})

TARGET_LINK_LIBRARIES(ASSET_TESTS Asset)

