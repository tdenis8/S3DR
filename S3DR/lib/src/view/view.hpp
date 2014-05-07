#ifndef _VIEW_H_
#define _VIEW_H_

#include "utility/subject.hpp"
#include "mouse_events_dispatcher.hpp"
#include "keyboard_events_dispatcher.hpp"
#include "view_adapter.hpp"

#include <glm/glm.hpp>
#include <memory>

// Forward declarations
class Projection;
class Camera;
class ViewAdapter;
class Model;
class Operator;
class SelectionSet;

enum class ViewEvent : unsigned int { ATTACH_MODEL,
                                      DETACH_MODEL, 
                                      WINDOW_RESIZE,
                                      // View settings changes
                                      VIEWER_SETTINGS_CHANGE
                                    };

struct ViewSettings {
    glm::vec3 background_color = glm::vec3(1.0,1.0,0.0);
};

class AttachModelInfo: public EventInfo {
    public:
        AttachModelInfo(Model & model) : 
            EventInfo(),  model(model) {}
        
        Model & ModelRef() const { return model; }

    private:
        Model & model;
};

class WindowResizeInfo: public EventInfo {
    public:
        WindowResizeInfo(int width, int height) : 
            EventInfo(),  width(width), height(height) {}
        
        const int & Width() const { return width; }
        const int & Height() const { return height; }

    private:
        int width;
        int height;
};

class View : public Subject<ViewEvent>, public MouseEventsDispatcher, public KeyboardEventsDispatcher {
    friend class CameraOperator;
    friend class ViewAdapter;

    public:
        View();
        View(const View &)=delete;
        View & operator=(const View &)=delete;
        virtual ~View();

        void AttachModel(Model * model);
        void DetachModel();
        Model * ModelPtr();

        void AttachOperator(Operator * opr);
        void DetachOperator();
        Operator * OperatorPtr();

        void Redraw();

        void WindowResize(int width, int height);

        // Viewer settings setters
        void SetBackgroundColor(const glm::vec3 & background_color);

        SelectionSet & GetSelectionSet();

    protected:
        Camera & CameraRef();
        Projection & ProjectionRef();
        const ViewSettings & ViewSettingsRef() const;
        float ScreenDepthAt(int x, int y) const;

    private:
        ViewSettings view_settings;

        std::unique_ptr<Projection> projection;     
        std::unique_ptr<Camera> camera;
        std::unique_ptr<SelectionSet> selection_set;
        std::unique_ptr<ViewAdapter> view_adapter;
        Model * model;
        Operator * opr;
};

#endif