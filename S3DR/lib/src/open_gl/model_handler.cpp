#include "model_handler.hpp"

#include "object_adapters/material_shell_adapter.hpp"
#include "object_adapters/texture_shell_adapter.hpp"
#include "object_adapters/line_adapter.hpp"
#include "object_adapters/point_adapter.hpp"
#include "object_adapters/text_adapter.hpp"

#include "object_renderers/selection_renderer.hpp"

ModelHandler::ModelHandler(Model& model, SceneRenderer& scene_renderer)
    : Observer(), model_(model), scene_renderer_(scene_renderer)
{
    std::vector<SceneObject*> scene_objects = model_.GetSceneObjects();
    for(auto scene_object_ptr : scene_objects)
    {
        NewSceneObject(SceneObjectInfo(scene_object_ptr));
    }

    model_.Observe(
        ModelEvents::NEW_SCENE_OBJECT, std::bind(&ModelHandler::NewSceneObject, this, std::placeholders::_1), this);

    model_.Observe(ModelEvents::REMOVE_SCENE_OBJECT,
                   std::bind(&ModelHandler::RemoveSceneObject, this, std::placeholders::_1),
                   this);

    model_.Observe(ModelEvents::RESET_MODEL, std::bind(&ModelHandler::ResetModel, this, std::placeholders::_1), this);
}

ModelHandler::~ModelHandler()
{
    model_.RemoveObservers(this);
}

void ModelHandler::NewSceneObject(const EventInfo& info)
{
    const SceneObjectInfo& so_info = dynamic_cast<const SceneObjectInfo&>(info);
    SceneObject* scene_object = so_info.GetSceneObject();

    if(MaterialShellObject* material_shell_object_ptr = dynamic_cast<MaterialShellObject*>(scene_object))
    {
        AttachtToMaterialShellRenderer(*material_shell_object_ptr);
    }
    else if(TextureShellObject* texture_shell_object_ptr = dynamic_cast<TextureShellObject*>(scene_object))
    {
        AttachtToTextureShellRenderer(*texture_shell_object_ptr);
    }
    else if(LineObject* line_object_ptr = dynamic_cast<LineObject*>(scene_object))
    {
        AttachtToLineRenderer(*line_object_ptr);
    }
    else if(PointObject* point_object_ptr = dynamic_cast<PointObject*>(scene_object))
    {
        AttachtToPointRenderer(*point_object_ptr);
    }
    else if(TextObject* text_object_ptr = dynamic_cast<TextObject*>(scene_object))
    {
        AttachtToTextRenderer(*text_object_ptr);
    }
    else
    {
        return;
    }
}

void ModelHandler::RemoveSceneObject(const EventInfo& info)
{
    const SceneObjectInfo& so_info = dynamic_cast<const SceneObjectInfo&>(info);
    SceneObject* scene_object = so_info.GetSceneObject();

    if(MaterialShellObject* material_shell_object_ptr = dynamic_cast<MaterialShellObject*>(scene_object))
    {
        DetachFromMaterialShellRenderer(*material_shell_object_ptr);
    }
    else if(TextureShellObject* texture_shell_object_ptr = dynamic_cast<TextureShellObject*>(scene_object))
    {
        DetachFromTextureShellRenderer(*texture_shell_object_ptr);
    }
    else if(LineObject* line_object_ptr = dynamic_cast<LineObject*>(scene_object))
    {
        DetachFromLineRenderer(*line_object_ptr);
    }
    else if(PointObject* point_object_ptr = dynamic_cast<PointObject*>(scene_object))
    {
        DetachFromPointRenderer(*point_object_ptr);
    }
    else if(TextObject* text_object_ptr = dynamic_cast<TextObject*>(scene_object))
    {
        DetachFromTextRenderer(*text_object_ptr);
    }
    else
    {
        return;
    }
}

void ModelHandler::ResetModel(const EventInfo& info)
{
    scene_renderer_.Reset();
    scene_object_adapters_.clear();
}

void ModelHandler::AttachtToMaterialShellRenderer(MaterialShellObject& shell_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<MaterialShellAdapter>(new MaterialShellAdapter(shell_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    MaterialShellAdapter* shell_adapter_ptr = dynamic_cast<MaterialShellAdapter*>(scene_object_adapter_ptr);
    scene_renderer_.GetMaterialShellRenderer().AttachMaterialShellAdapter(shell_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelHandler::AttachtToTextureShellRenderer(TextureShellObject& texture_shell_object)
{
    scene_object_adapters_.push_back(
        std::unique_ptr<TextureShellAdapter>(new TextureShellAdapter(texture_shell_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    TextureShellAdapter* texture_shell_adapter_ptr = dynamic_cast<TextureShellAdapter*>(scene_object_adapter_ptr);
    scene_renderer_.GetTextureShellRenderer().AttachTextureShellAdapter(texture_shell_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelHandler::AttachtToLineRenderer(LineObject& line_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<LineAdapter>(new LineAdapter(line_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    LineAdapter* line_adapter_ptr = dynamic_cast<LineAdapter*>(scene_object_adapter_ptr);
    scene_renderer_.GetLineRenderer().AttachLineAdapter(line_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelHandler::AttachtToPointRenderer(PointObject& point_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<PointAdapter>(new PointAdapter(point_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    PointAdapter* point_adapter_ptr = dynamic_cast<PointAdapter*>(scene_object_adapter_ptr);
    scene_renderer_.GetPointRenderer().AttachPointAdapter(point_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelHandler::AttachtToTextRenderer(TextObject& text_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<TextAdapter>(new TextAdapter(text_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    TextAdapter* text_adapter_ptr = dynamic_cast<TextAdapter*>(scene_object_adapter_ptr);
    scene_renderer_.GetTextRenderer().AttachTextAdapter(text_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelHandler::AttachtToSelectionRenderer(SceneObjectAdapter* scene_object_adapter_ptr)
{
    scene_renderer_.GetSelectionRenderer().AttachSceneObjectAdapter(scene_object_adapter_ptr);
}

void ModelHandler::DetachFromMaterialShellRenderer(MaterialShellObject& shell_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == shell_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            MaterialShellAdapter* shell_adapter_ptr = dynamic_cast<MaterialShellAdapter*>(scene_object_adapter_ptr);
            scene_renderer_.GetMaterialShellRenderer().DetachMaterialShellAdapter(shell_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelHandler::DetachFromTextureShellRenderer(TextureShellObject& texture_shell_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == texture_shell_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            TextureShellAdapter* texture_shell_adapter_ptr =
                dynamic_cast<TextureShellAdapter*>(scene_object_adapter_ptr);
            scene_renderer_.GetTextureShellRenderer().DetachTextureShellAdapter(texture_shell_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelHandler::DetachFromLineRenderer(LineObject& line_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == line_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            LineAdapter* line_adapter_ptr = dynamic_cast<LineAdapter*>(scene_object_adapter_ptr);
            scene_renderer_.GetLineRenderer().DetachLineAdapter(line_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelHandler::DetachFromPointRenderer(PointObject& point_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == point_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            PointAdapter* point_adapter_ptr = dynamic_cast<PointAdapter*>(scene_object_adapter_ptr);
            scene_renderer_.GetPointRenderer().DetachPointAdapter(point_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelHandler::DetachFromTextRenderer(TextObject& text_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == text_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            TextAdapter* text_adapter_ptr = dynamic_cast<TextAdapter*>(scene_object_adapter_ptr);
            scene_renderer_.GetTextRenderer().DetachTextAdapter(text_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelHandler::DetachFromSelectionRenderer(SceneObjectAdapter* scene_object_adapter_ptr)
{
    scene_renderer_.GetSelectionRenderer().DetachSceneObjectAdapter(scene_object_adapter_ptr);
}