#include "dual_depth_peeling.hpp"

#include "../transparency_renderer.hpp"
#include <iostream>

DualDepthPeeling::DualDepthPeeling(TransparencyRenderer & transparency_renderer):
	transparency_renderer(transparency_renderer)
{
	//generate the quad vertices
	glm::vec2 quadVerts[4];
	quadVerts[0] = glm::vec2(0,0);
	quadVerts[1] = glm::vec2(1,0);
	quadVerts[2] = glm::vec2(1,1);
	quadVerts[3] = glm::vec2(0,1);

	//generate quad indices 
	GLushort quadIndices[]={ 0,1,2,0,2,3};

	//generate quad  vertex array and vertex buffer objects
	glGenVertexArrays(1, &quadVAOID);
	glGenBuffers(1, &quadVBOID);
	glGenBuffers(1, &quadIndicesID);

	glBindVertexArray(quadVAOID);
	glBindBuffer (GL_ARRAY_BUFFER, quadVBOID);
	//pass quad vertices to buffer object memory
	glBufferData (GL_ARRAY_BUFFER, sizeof(quadVerts), &quadVerts[0], GL_STATIC_DRAW);


	//enable vertex attribute array for position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,0,0);

	//pass the quad indices to the element array buffer
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, quadIndicesID);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), &quadIndices[0], GL_STATIC_DRAW);
}

DualDepthPeeling::~DualDepthPeeling(){
	FreeFBO();
}

//FBO initialization function
void DualDepthPeeling::InitFBO(int width, int height){
	//generate dual depth FBO
	glGenFramebuffers(1, &dual_depth_FBO);
	//The FBO has 4 colour attachments
	glGenTextures (2, dd_front_color_textures);
	glGenTextures (2, dd_back_color_textures);
	//The FBO has 2 depth attachments
	glGenTextures (2, dd_depth_textures);
	//first pass depth texture
	glGenTextures (1, &dd_first_pass_depth_texture);

	//for each attachment
	for(int i=0;i<2;i++) {
		//first initialize the depth texture
		glBindTexture(GL_TEXTURE_RECTANGLE, dd_depth_textures[i]);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_RECTANGLE , 0, GL_FLOAT_RG32_NV, width, height, 0, GL_RGB, GL_FLOAT, NULL);

		//initialize the colour attachment
		glBindTexture(GL_TEXTURE_RECTANGLE,dd_front_color_textures[i]);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_RECTANGLE , 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

		//initialize the back colour attachment
		glBindTexture(GL_TEXTURE_RECTANGLE,dd_back_color_textures[i]);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_RECTANGLE , 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	}

	//initialize the first pass depth attachment
	glBindTexture(GL_TEXTURE_RECTANGLE, dd_first_pass_depth_texture);
	glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_RECTANGLE , GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_RECTANGLE , 0, GL_FLOAT_RG32_NV, width, height, 0, GL_RGB, GL_FLOAT, NULL);


	//Now setup the colour attachment for colour blend FBO
	
	//generate the colour blend FBO ID
	glGenFramebuffers(1, &color_blender_FBO);
	//The colour blend FBO colour attachment
	glGenTextures(1, &cb_color_texture);

	//initialize the colour attachment
	glBindTexture(GL_TEXTURE_RECTANGLE, cb_color_texture);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, 0);


	//bind the dual depth FBO
	glBindFramebuffer(GL_FRAMEBUFFER, dual_depth_FBO);

	//color attachment IDs
	GLenum color_attachments[2]={GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT3};

	//bind the six colour attachments for this FBO
	for(int i=0;i<2;i++) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, color_attachments[i], GL_TEXTURE_RECTANGLE, dd_depth_textures[i], 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, color_attachments[i]+1, GL_TEXTURE_RECTANGLE, dd_front_color_textures[i], 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, color_attachments[i]+2, GL_TEXTURE_RECTANGLE, dd_back_color_textures[i], 0);
	}

	//set the colour blender texture as the 7th attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_RECTANGLE, cb_color_texture, 0);
	
	//set the first pass depth texture as the 8th attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_RECTANGLE, dd_first_pass_depth_texture, 0);


	//bind the color blend FBO
	glBindFramebuffer(GL_FRAMEBUFFER, color_blender_FBO);
	//set the colour blender texture as the FBO colour attachment 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_RECTANGLE, cb_color_texture, 0);


	//check the FBO completeness status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE ){
		std::cerr<<"Problem with FBO setup"<<std::endl;
	}

	//unbind FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//delete all FBO related resources
void DualDepthPeeling::FreeFBO() {
	glDeleteFramebuffers(1, &dual_depth_FBO);
	glDeleteFramebuffers(1, &color_blender_FBO);
	glDeleteTextures(2, dd_front_color_textures);
	glDeleteTextures(2, dd_back_color_textures);
	glDeleteTextures(2, dd_depth_textures);
	glDeleteTextures(1, &dd_first_pass_depth_texture);
	glDeleteTextures(1, &cb_color_texture);
}

//function to draw a fullscreen quad
void DualDepthPeeling::DrawFullScreenQuad() {
	//bind the quad vertex array object
	glBindVertexArray(quadVAOID);
	//draw 2 triangles
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void DualDepthPeeling::SetWidthHeight(int width, int height){
	FreeFBO();
	InitFBO(width, height);
}

void DualDepthPeeling::SetBackgroundColor(const glm::vec4 & background_color){
	this->background_color = background_color;
}

void DualDepthPeeling::Render(std::function<void(void)> redraw_callback){
	//disble depth test and enable alpha blending
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	//bind dual depth FBO
	glBindFramebuffer(GL_FRAMEBUFFER, dual_depth_FBO);

	// Render targets 1 and 2 store the front and back colors
	// Clear to 0.0 and use MAX blending to filter written color
	// At most one front color and one back color can be written every pass
	glDrawBuffers(2, &draw_buffer_attachments0[1]);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Render target 0 stores (-minDepth, maxDepth)
	// clear the offscreen texture with -MAX_DEPTH
	glDrawBuffers(2, &draw_buffer_attachments1[0]);
	glClearColor(-MAX_DEPTH, -MAX_DEPTH, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//render scene with the initialization shader
	//enable max blending
	glBlendEquation(GL_MAX);

	transparency_renderer.ActivateProgram(DDPPassType::INIT);
	redraw_callback();
	transparency_renderer.DeactivateProgram();

	// 2. Depth peeling + blending pass
	// clear color buffer with the background colour
	glDrawBuffer(GL_COLOR_ATTACHMENT6);
	glClearColor(background_color.x, background_color.y, background_color.z, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	 
	int currId = 0;
	//for each pass
	for (int layer = 1; bUseOQ || layer < NUM_PASSES; layer++) {
		currId = layer % 2;
		int prevId = 1 - currId;
		int bufId = currId * 3;

		//render to 2 colour attachments simultaneously
		glDrawBuffers(2, &draw_buffer_attachments0[bufId+1]);
		//set clear color to black and clear colour buffer
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//alternate the colour attachment for draw buffer
		glDrawBuffer(draw_buffer_attachments0[bufId+0]);
		//clear the color to -MAX_DEPTH and clear colour buffer
		glClearColor(-MAX_DEPTH, -MAX_DEPTH, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render to three draw buffers simultaneously
		// Render target 0: RG32F MAX blending
		// Render target 1: RGBA MAX blending
		// Render target 2: RGBA MAX blending
		glDrawBuffers(3, &draw_buffer_attachments0[bufId+0]);	
		//enable max blending
		glBlendEquation(GL_MAX);
		
		//draw scene using the dual peel shader 
		transparency_renderer.ActivateProgram(DDPPassType::PEEL);
		transparency_renderer.BindTexture(GL_TEXTURE_RECTANGLE, "depthBlenderTex",dd_depth_textures[prevId], 0);
		transparency_renderer.BindTexture(GL_TEXTURE_RECTANGLE, "frontBlenderTex",dd_front_color_textures[prevId], 1);
		redraw_callback();
		transparency_renderer.DeactivateProgram();

		// Full screen pass to alpha-blend the back color
		glDrawBuffer(GL_COLOR_ATTACHMENT6);

		//set the over blending 
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		 
		//if we want to use occlusion query, we initiate it
		if (bUseOQ) {
			glBeginQuery(GL_SAMPLES_PASSED_ARB, queryId);
		}

		//bind the back colour attachment to texture unit 0
		//use blending shader and draw a fullscreen quad
		transparency_renderer.ActivateProgram(DDPPassType::BLEND);
		transparency_renderer.BindTexture(GL_TEXTURE_RECTANGLE, "tempTexture",dd_back_color_textures[currId], 0);
		DrawFullScreenQuad();
		transparency_renderer.DeactivateProgram();

		//if we initiated the occlusion query, we end it and get
		//the query result which is the total number of samples
		//output from the blending result
		if (bUseOQ) {
			glEndQuery(GL_SAMPLES_PASSED);
			GLuint sample_count;
			glGetQueryObjectuiv(queryId, GL_QUERY_RESULT, &sample_count);
			if (sample_count == 0) {
				break;
			}
		}
	}

	// 3. Final render pass
	// Blend ddp result with main FBO content
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);

	// Enable depth test, but don't change z-buffer
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	//remove the FBO 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//restore the default back buffer
	glDrawBuffer(GL_BACK_LEFT);
	
	transparency_renderer.ActivateProgram(DDPPassType::FINAL);
	transparency_renderer.BindTexture(GL_TEXTURE_RECTANGLE, "depthBlenderTex",dd_first_pass_depth_texture, 0);
	transparency_renderer.BindTexture(GL_TEXTURE_RECTANGLE, "frontBlenderTex",dd_front_color_textures[currId], 1);
	transparency_renderer.BindTexture(GL_TEXTURE_RECTANGLE, "backBlenderTex",cb_color_texture, 2);
	DrawFullScreenQuad();
	transparency_renderer.DeactivateProgram();

	// Restore some settings
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
    glDepthRange(0.0f, 1.0f);
    glClearColor(background_color.x, background_color.y, background_color.z, 0);  
}