#ifndef _MODEL_ADAPTER_H_
#define _MODEL_ADAPTER_H_

#include "model/model.hpp"

#include <memory>

class ShellObject;
class TextureShellObject;
class LineObject;
class PointObject;
class TextObject;

class SceneManager;
class SceneObjectAdapter;

class ModelAdapter : Observer
{
    public:
    ModelAdapter() = delete;
    ModelAdapter(Model &model, SceneManager &scene_manager);
    ModelAdapter(const ModelAdapter &) = delete;
    ModelAdapter(ModelAdapter &&) = delete;
    ModelAdapter &operator=(const ModelAdapter &) = delete;
    virtual ~ModelAdapter();

    private:
    void NewSceneObject(const EventInfo &info);
    void RemoveSceneObject(const EventInfo &info);
    void ResetModel(const EventInfo &info);

    void AttachtToShellRenderer(ShellObject &shell_object);
    void AttachtToTextureShellRenderer(TextureShellObject &texture_shell_object);
    void AttachtToLineRenderer(LineObject &line_object);
    void AttachtToPointRenderer(PointObject &point_object);
    void AttachtToTextRenderer(TextObject &text_object);
    void AttachtToSelectionRenderer(SceneObjectAdapter *scene_object_adapter);

    void DetachFromShellRenderer(ShellObject &shell_object);
    void DetachFromTextureShellRenderer(TextureShellObject &texture_shell_object);
    void DetachFromLineRenderer(LineObject &line_object);
    void DetachFromPointRenderer(PointObject &point_object);
    void DetachFromTextRenderer(TextObject &text_object);
    void DetachFromSelectionRenderer(SceneObjectAdapter *scene_object_adapter_ptr);

    Model &model_;
    SceneManager &scene_manager_;
    std::vector<std::unique_ptr<SceneObjectAdapter> > scene_object_adapters_;
};

#endif