#include "selection_texture.hpp"

#include <iostream>

SelectionTexture::SelectionTexture():
	fbo(-1),
    picking_texture(-1),
    depth_texture(-1)
{

}

SelectionTexture::~SelectionTexture(){
	FreeTexture();
}

void SelectionTexture::InitTexture(int width, int height){
    // Create the FBO
    glGenFramebuffers(1, &fbo); 
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create the texture object for the primitive information buffer
    glGenTextures(1, &picking_texture);
    glBindTexture(GL_TEXTURE_2D, picking_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, width, height,
                0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
                picking_texture, 0); 

    // Create the texture object for the depth buffer
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 
                0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
                depth_texture, 0); 


    //check the FBO completeness status
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE ){
        std::cerr<<"Problem with FBO setup."<<std::endl;
    }

    // Disable reading to avoid problems with older GPUs
    glReadBuffer(GL_NONE);

    // Restore the default framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SelectionTexture::FreeTexture(){
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &picking_texture);
    glDeleteTextures(1, &depth_texture);
}

void SelectionTexture::SetWidthHeight(int width, int height){
    this->height = height;
    FreeTexture();
    InitTexture(width, height);
}

void SelectionTexture::EnableWriting(){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void SelectionTexture::DisableWriting(){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

SelectionData SelectionTexture::GetSelectionData(unsigned int x, unsigned int y){
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0);

    SelectionData pixel;
    glReadPixels(x, height - y -1, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &pixel);

    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    return pixel;
}