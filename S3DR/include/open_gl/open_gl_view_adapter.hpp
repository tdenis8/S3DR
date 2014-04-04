#ifndef _OPEN_GL_VIEW_ADAPTER_H_
#define _OPEN_GL_VIEW_ADAPTER_H_

#include "view/view_adapter.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

// Forward declarations
class ModelAdapter;
class SceneSettings;
class SceneManager;
class SelectionSet;
class EventInfo;


class OpenGLViewAdapter: public ViewAdapter {
    public:
        OpenGLViewAdapter(View & view);
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

        std::unique_ptr<SceneSettings> scene_settings;
        std::unique_ptr<SceneManager> scene_manager;
    	std::unique_ptr<ModelAdapter> model_adapter;
        
        std::vector<unsigned int> view_observer_ids;
        std::vector<unsigned int> selection_set_observer_ids;
};

#endif