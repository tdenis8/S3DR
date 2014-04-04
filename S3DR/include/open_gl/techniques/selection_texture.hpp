#ifndef _SELECTION_TEXTURE_HPP_
#define _SELECTION_TEXTURE_HPP_

#include "view/selection_set.hpp"
#include <GL/glew.h>

class SelectionTexture {
    public:
        SelectionTexture();
        ~SelectionTexture();
        SelectionTexture(const SelectionTexture &)=delete;
        SelectionTexture & operator=(const SelectionTexture &)=delete;

        void SetWidthHeight(int width, int height);

        void EnableWriting();
        void DisableWriting();

        SelectionData GetSelectionData(unsigned int x, unsigned int y);

    private:
        void InitTexture(int width, int height);
        void FreeTexture();

   		GLuint fbo;
    	GLuint picking_texture;
    	GLuint depth_texture;

        int height;
};

#endif