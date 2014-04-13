#ifndef _MODEL_ADAPTER_H_
#define _MODEL_ADAPTER_H_

#include "model/model.hpp"

#include <memory>

class ShellObject;
class TextureShellObject;
class LineObject;
class PointObject;

class SceneManager;
class SceneObjectAdapter;

class ModelAdapter: Observer {
    public:
        ModelAdapter(Model & model, SceneManager & scene_manager);
        virtual ~ModelAdapter();

    private:
    	void NewSceneObject(const EventInfo & info);
        void RemoveSceneObject(const EventInfo & info);
        void ResetModel(const EventInfo & info);

        void AttachtToShellRenderer(ShellObject * shell_object_ptr);
        void AttachtToTextureShellRenderer(TextureShellObject * texture_shell_object_ptr);
        void AttachtToLineRenderer(LineObject * line_object_ptr);
        void AttachtToPointRenderer(PointObject * point_object_ptr);
        void AttachtToSelectionRenderer(SceneObjectAdapter * scene_object_adapter_ptr);

        void DetachFromShellRenderer(ShellObject * shell_object_ptr);
        void DetachFromTextureShellRenderer(TextureShellObject * texture_shell_object_ptr);
        void DetachFromLineRenderer(LineObject * line_object_ptr);
        void DetachFromPointRenderer(PointObject * point_object_ptr);
        void DetachFromSelectionRenderer(SceneObjectAdapter * scene_object_adapter_ptr);

    	Model & model;
        SceneManager & scene_manager;

    	std::vector<std::unique_ptr<SceneObjectAdapter>> scene_object_adapters; 
};

#endif