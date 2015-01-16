#ifndef _MODEL_ADAPTER_H_
#define _MODEL_ADAPTER_H_

#include "model/model.hpp"

#include "scene_renderer.hpp"

#include <memory>

class MaterialShellObject;
class TextureShellObject;
class LineObject;
class PointObject;
class TextObject;

class SceneObjectAdapter;

class ModelHandler : Observer
{
    public:
    ModelHandler() = delete;
    ModelHandler(Model &model, SceneRenderer &scene_renderer);
    ModelHandler(const ModelHandler &) = delete;
    ModelHandler(ModelHandler &&) = delete;
    ModelHandler &operator=(const ModelHandler &) = delete;
    virtual ~ModelHandler();

    private:
    void NewSceneObject(const EventInfo &info);
    void RemoveSceneObject(const EventInfo &info);
    void ResetModel(const EventInfo &info);

    void AttachtToMaterialShellRenderer(MaterialShellObject &material_shell_object);
    void AttachtToTextureShellRenderer(TextureShellObject &texture_shell_object);
    void AttachtToLineRenderer(LineObject &line_object);
    void AttachtToPointRenderer(PointObject &point_object);
    void AttachtToTextRenderer(TextObject &text_object);
    void AttachtToSelectionRenderer(SceneObjectAdapter *scene_object_adapter);

    void DetachFromMaterialShellRenderer(MaterialShellObject &material_shell_object);
    void DetachFromTextureShellRenderer(TextureShellObject &texture_shell_object);
    void DetachFromLineRenderer(LineObject &line_object);
    void DetachFromPointRenderer(PointObject &point_object);
    void DetachFromTextRenderer(TextObject &text_object);
    void DetachFromSelectionRenderer(SceneObjectAdapter *scene_object_adapter_ptr);

    Model &model_;
    SceneRenderer &scene_renderer_;

    std::vector<std::unique_ptr<SceneObjectAdapter> > scene_object_adapters_;
};

#endif