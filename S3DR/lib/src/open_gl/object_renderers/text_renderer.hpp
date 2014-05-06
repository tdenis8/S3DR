#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include "scene_object_renderer.hpp"

#include <glm/glm.hpp>

#include <vector>

class TextAdapter;

class TextRenderer: public SceneObjectRenderer {
    public:
        TextRenderer();
        TextRenderer(const TextRenderer &)=delete;
        TextRenderer & operator=(const TextRenderer &)=delete;
        ~TextRenderer();

        void AttachTextAdapter(TextAdapter * text_adapter);
        void DetachTextAdapter(TextAdapter * text_adapter);
        void Reset();
        
        void Render(const glm::mat4 & view, const glm::mat4 & projection, int priority);

    private:
    	void InitProgram();
        
        void SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix);

		std::vector<TextAdapter *> text_adapters[3];
};
    
#endif