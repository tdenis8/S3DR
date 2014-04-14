# S3DR - Small 3D renderer
# ========================

PROJECT(S3DR)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# ========================
# S3DR lib
# ========================
# Set source variables
SET(S3DR_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

SET(S3DR_LIB_SCR_AUXILIARY ${S3DR_LIB_SRC_DIR}/auxiliary/geometry_object.cpp
                           ${S3DR_LIB_SRC_DIR}/auxiliary/geometry_utils.cpp)

SET(S3DR_LIB_SCR_MODEL ${S3DR_LIB_SRC_DIR}/model/line_object.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/model.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/point_object.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/scene_object.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/shell_object.cpp 
                       ${S3DR_LIB_SRC_DIR}/model/texture_shell_object.cpp)

SET(S3DR_LIB_SCR_OPENGL ${S3DR_LIB_SRC_DIR}/open_gl/model_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/open_gl_view_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/scene_manager.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/scene_settings.cpp

                        ${S3DR_LIB_SRC_DIR}/open_gl/misc/lights.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/misc/program.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/misc/shader.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/misc/texture.cpp

                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/line_adapter.cpp   
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/scene_object_adapter.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/texture_shell_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/point_adapter.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/shell_adapter.cpp

                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/line_renderer.cpp          
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/selection_renderer.cpp      
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/transparency_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/point_renderer.cpp         
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/shell_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/scene_object_renderer.cpp 
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/texture_shell_renderer.cpp

                        ${S3DR_LIB_SRC_DIR}/open_gl/techniques/dual_depth_peeling.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/techniques/selection_texture.cpp)

SET(S3DR_LIB_SCR_OPERATOR ${S3DR_LIB_SRC_DIR}/operator/camera_operator.cpp  
                          ${S3DR_LIB_SRC_DIR}/operator/operator.cpp
                          ${S3DR_LIB_SRC_DIR}/operator/select_operator.cpp)

SET(S3DR_LIB_SCR_VIEW ${S3DR_LIB_SRC_DIR}/view/camera.cpp
                      ${S3DR_LIB_SRC_DIR}/view/keyboard_events_dispatcher.cpp
                      ${S3DR_LIB_SRC_DIR}/view/mouse_events_dispatcher.cpp
                      ${S3DR_LIB_SRC_DIR}/view/projection.cpp
                      ${S3DR_LIB_SRC_DIR}/view/selection_set.cpp
                      ${S3DR_LIB_SRC_DIR}/view/view_adapter.cpp
                      ${S3DR_LIB_SRC_DIR}/view/view.cpp)

SET(S3DR_LIB_SRC_ALL ${S3DR_LIB_SCR_AUXILIARY}
                     ${S3DR_LIB_SCR_MODEL}
                     ${S3DR_LIB_SCR_OPENGL}
                     ${S3DR_LIB_SCR_OPERATOR}
                     ${S3DR_LIB_SCR_VIEW})

# Set include directories
SET(S3DR_LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

INCLUDE_DIRECTORIES(${S3DR_LIB_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Utility/lib/src)

# Build library
ADD_LIBRARY(S3DR STATIC ${S3DR_LIB_SRC_ALL})
TARGET_LINK_LIBRARIES(S3DR Utility)
TARGET_LINK_LIBRARIES(S3DR SOIL
                           GL
                           GLEW)
#ADD_DEPENDENCIES(S3DR Utility)

# ========================
# S3DR tests
# ========================
# Set source variables
SET(S3DR_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

SET(S3DR_TEST_SRC ${S3DR_TESTS_SRC_DIR}/auxiliary_tests.cpp
                  ${S3DR_TESTS_SRC_DIR}/model_tests.cpp    
                  ${S3DR_TESTS_SRC_DIR}/main.cpp)

SET(S3DR_TESTS_SRC_ALL ${S3DR_TEST_SRC}
                       ${S3DR_TEST_SRC_MISC})

# Set include directories
SET(S3DR_TESTS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

INCLUDE_DIRECTORIES(${S3DR_TESTS_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Asset/lib/src)

# Build executabele
ADD_EXECUTABLE(S3DR_TESTS ${S3DR_TESTS_SRC_ALL})

TARGET_LINK_LIBRARIES(S3DR_TESTS S3DR 
                                 Asset
                                 Utility)
