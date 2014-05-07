#ifndef _OPEN_GL_VIEW_ADAPTER_H_
#define _OPEN_GL_VIEW_ADAPTER_H_

#include "utility/subject.hpp"
#include "view/view_adapter.hpp"
#include "view/selection_set.hpp"
#include "scene_settings.hpp"
#include "scene_manager.hpp"
#include "model_adapter.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

class OpenGLInitazer{
    public:
        OpenGLInitazer();
};

class OpenGLViewAdapter: public ViewAdapter, Observer {
    public:
        OpenGLViewAdapter()=delete;
        explicit OpenGLViewAdapter(View & view);
        OpenGLViewAdapter(const OpenGLViewAdapter &)=delete;
        OpenGLViewAdapter(OpenGLViewAdapter &&)=delete;
        OpenGLViewAdapter & operator=(const OpenGLViewAdapter &)=delete;
        OpenGLViewAdapter & operator=(OpenGLViewAdapter &&)=delete;
        virtual ~OpenGLViewAdapter();

        void Render(const glm::mat4 & view_matrix, const glm::mat4 & projection_matrix);
        float ScreenDepthAt(int x, int y) const;

    private:
    	void AttachModel(const EventInfo & info);
        void DetachModel(const EventInfo & info);
        void WindowResize(const EventInfo & info);
        void ViewerSettingsChange(const EventInfo & info);
        void CalculateSelection(const EventInfo & info);

        SelectionSet & selection_set;
        
        OpenGLInitazer open_gl_initazer;
        SceneSettings scene_settings;
        SceneManager scene_manager;
    	std::unique_ptr<ModelAdapter> model_adapter;
};

#endif