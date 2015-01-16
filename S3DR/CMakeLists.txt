# S3DR - Small 3D renderer
# ========================

PROJECT(S3DR)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#ADD_SUBDIRECTORY(lib/third_party/freetype-gl)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(ImageMagick COMPONENTS Magick++)
PKG_SEARCH_MODULE(GLEW REQUIRED glew)
PKG_SEARCH_MODULE(FREETYPE REQUIRED freetype2)

# ========================
# S3DR lib
# ========================
# Set source variables
SET(S3DR_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

SET(S3DR_LIB_SRC_AUXILIARY ${S3DR_LIB_SRC_DIR}/auxiliary/geometry_object.cpp
                           ${S3DR_LIB_SRC_DIR}/auxiliary/geometry_utils.cpp)

SET(S3DR_LIB_SRC_MODEL ${S3DR_LIB_SRC_DIR}/model/line_object.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/model.cpp
                       ${S3DR_LIB_SRC_DIR}/model/model_manager.cpp 
                       ${S3DR_LIB_SRC_DIR}/model/point_object.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/scene_object.cpp  
                       ${S3DR_LIB_SRC_DIR}/model/material_shell_object.cpp
                       ${S3DR_LIB_SRC_DIR}/model/text_object.cpp 
                       ${S3DR_LIB_SRC_DIR}/model/texture_shell_object.cpp)

SET(S3DR_LIB_SRC_OPENGL ${S3DR_LIB_SRC_DIR}/open_gl/model_handler.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/open_gl_view_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/scene_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/scene_settings.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/lights_handler.cpp

                        ${S3DR_LIB_SRC_DIR}/open_gl/misc/selection_texture.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/misc/base_texture.cpp  

                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/line_adapter.cpp   
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/scene_object_adapter.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/texture_shell_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/point_adapter.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/material_shell_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/text_adapter.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/fonts/font_handler.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/fonts/atlas_texture.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_adapters/misc/texture.cpp

                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/line_renderer.cpp          
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/selection_renderer.cpp      
                        #${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/transparency_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/point_renderer.cpp         
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/material_shell_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/text_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/scene_object_renderer.cpp 
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/texture_shell_renderer.cpp
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/misc/dual_depth_peeling.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/misc/program.cpp  
                        ${S3DR_LIB_SRC_DIR}/open_gl/object_renderers/misc/shader.cpp)

SET(S3DR_LIB_SRC_OPERATOR ${S3DR_LIB_SRC_DIR}/operator/camera_operator.cpp  
                          ${S3DR_LIB_SRC_DIR}/operator/operator.cpp
                          ${S3DR_LIB_SRC_DIR}/operator/select_operator.cpp)

SET(S3DR_LIB_SRC_VIEW ${S3DR_LIB_SRC_DIR}/view/camera.cpp
                      ${S3DR_LIB_SRC_DIR}/view/light.cpp
                      ${S3DR_LIB_SRC_DIR}/view/lights_manager.cpp
                      ${S3DR_LIB_SRC_DIR}/view/keyboard_events_dispatcher.cpp
                      ${S3DR_LIB_SRC_DIR}/view/mouse_events_dispatcher.cpp
                      ${S3DR_LIB_SRC_DIR}/view/selection_set.cpp
                      ${S3DR_LIB_SRC_DIR}/view/view_adapter.cpp
                      ${S3DR_LIB_SRC_DIR}/view/view.cpp)

SET(S3DR_LIB_SRC_ALL ${S3DR_LIB_SRC_AUXILIARY}
                     ${S3DR_LIB_SRC_MODEL}
                     ${S3DR_LIB_SRC_OPENGL}
                     ${S3DR_LIB_SRC_OPERATOR}
                     ${S3DR_LIB_SRC_VIEW})

# Set include directories
SET(S3DR_LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src)

INCLUDE_DIRECTORIES(${S3DR_LIB_INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Utility/lib/src)
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib/third_party)
INCLUDE_DIRECTORIES(${ImageMagick_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})

# Build library
ADD_LIBRARY(S3DR STATIC ${S3DR_LIB_SRC_ALL})
TARGET_LINK_LIBRARIES(S3DR Utility)
TARGET_LINK_LIBRARIES(S3DR ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES(S3DR ${GLEW_LIBRARIES})
TARGET_LINK_LIBRARIES(S3DR ${ImageMagick_LIBRARIES})
TARGET_LINK_LIBRARIES(S3DR ${FREETYPE_LIBRARIES})
