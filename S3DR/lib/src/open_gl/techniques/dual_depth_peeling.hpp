#ifndef _DUAL_DEPTH_PEELING_H_
#define _DUAL_DEPTH_PEELING_H_

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <functional>

class TransparencyRenderer;

class DualDepthPeeling {
    public:
    	DualDepthPeeling() = delete;
        DualDepthPeeling(TransparencyRenderer & transparency_renderer);
        DualDepthPeeling(const DualDepthPeeling &) = delete;
        DualDepthPeeling& operator=(const DualDepthPeeling&) = delete;
        virtual ~DualDepthPeeling();

        void SetWidthHeight(int width, int height);
        void SetBackgroundColor(const glm::vec4 & background_color);

        void Render(std::function<void(void)> redraw_callback);

    private:
    	void InitFBO(int width, int height);
		void FreeFBO();

		void DrawFullScreenQuad();

		//total number of depth peeling passes
		const int NUM_PASSES=8;
		const float MAX_DEPTH = 1.0f;
		//flag to use occlusion queries
		bool bUseOQ = true;
		//background colour
		glm::vec4 background_color=glm::vec4(1,1,1,0);

	
		//dual depth peeling FBO id
		GLuint dual_depth_FBO;
		//back texture colour attachment IDs
		GLuint dd_back_color_textures[2];
		//front texture colour attachment IDs
		GLuint dd_front_color_textures[2];
		//back texture depth attachment IDs
		GLuint dd_depth_textures[2];
		//first pass depth texture
		GLuint dd_first_pass_depth_texture;

		//colour blending FBO ID
		GLuint color_blender_FBO;
		//colour blend FBO colour attachment texture ID
		GLuint cb_color_texture;

		//draw buffer attachments
		GLenum draw_buffer_attachments0[6] = {GL_COLOR_ATTACHMENT0,
								 			  GL_COLOR_ATTACHMENT1,
								 			  GL_COLOR_ATTACHMENT2,
								 			  GL_COLOR_ATTACHMENT3,
								 			  GL_COLOR_ATTACHMENT4,
								 			  GL_COLOR_ATTACHMENT5};

		GLenum draw_buffer_attachments1[2] = {GL_COLOR_ATTACHMENT0,
											  GL_COLOR_ATTACHMENT7};

		//occlusion query ID
		GLuint queryId;

		//fullscreen quad vao and vbos
		GLuint quadVAOID;
		GLuint quadVBOID;
		GLuint quadIndicesID;

		TransparencyRenderer & transparency_renderer;
};

#endif