#include "model_adapter.hpp"

#include "object_adapters/shell_adapter.hpp"
#include "object_adapters/texture_shell_adapter.hpp"
#include "object_adapters/line_adapter.hpp"
#include "object_adapters/point_adapter.hpp"
#include "object_adapters/text_adapter.hpp"
#include "object_renderers/selection_renderer.hpp"
#include "object_renderers/transparency_renderer.hpp"
#include "scene_manager.hpp"

ModelAdapter::ModelAdapter(Model& model, SceneManager& scene_manager)
    : Observer(), model_(model), scene_manager_(scene_manager)
{
    std::vector<SceneObject*> scene_objects = model_.GetSceneObjects();
    for(auto scene_object_ptr : scene_objects)
    {
        NewSceneObject(SceneObjectInfo(scene_object_ptr));
    }

    model_.Observe(
        ModelEvents::NEW_SCENE_OBJECT, std::bind(&ModelAdapter::NewSceneObject, this, std::placeholders::_1), this);

    model_.Observe(ModelEvents::REMOVE_SCENE_OBJECT,
                   std::bind(&ModelAdapter::RemoveSceneObject, this, std::placeholders::_1),
                   this);

    model_.Observe(ModelEvents::RESET_MODEL, std::bind(&ModelAdapter::ResetModel, this, std::placeholders::_1), this);
}

ModelAdapter::~ModelAdapter()
{
    model_.RemoveObservers(this);
}

void ModelAdapter::NewSceneObject(const EventInfo& info)
{
    const SceneObjectInfo& so_info = dynamic_cast<const SceneObjectInfo&>(info);
    SceneObject* scene_object = so_info.GetSceneObject();

    if(ShellObject* shell_object_ptr = dynamic_cast<ShellObject*>(scene_object))
    {
        if(shell_object_ptr->TestObjectOption(static_cast<unsigned int>(ShellOption::Transparency)))
        {
            // TransparencyRenderer & transparency_renderer = scene_manager.TransparencyRendererRef();
            // transparency_renderer.AttachShellAdapter(shell_adapter);
        }
        else
        {
            AttachtToShellRenderer(*shell_object_ptr);
        }
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

void ModelAdapter::RemoveSceneObject(const EventInfo& info)
{
    const SceneObjectInfo& so_info = dynamic_cast<const SceneObjectInfo&>(info);
    SceneObject* scene_object = so_info.GetSceneObject();

    if(ShellObject* shell_object_ptr = dynamic_cast<ShellObject*>(scene_object))
    {
        if(shell_object_ptr->TestObjectOption(static_cast<unsigned int>(ShellOption::Transparency)))
        {
            // TransparencyRenderer & transparency_renderer = scene_manager.TransparencyRendererRef();
            // transparency_renderer.AttachShellAdapter(shell_adapter);
        }
        else
        {
            DetachFromShellRenderer(*shell_object_ptr);
        }
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

void ModelAdapter::ResetModel(const EventInfo& info)
{
    scene_manager_.GetShellRenderer().Reset();
    scene_manager_.GetTransparencyRenderer().Reset();
    scene_manager_.GetTextureShellRenderer().Reset();
    scene_manager_.GetSelectionRenderer().Reset();
    scene_manager_.GetLineRenderer().Reset();
    scene_manager_.GetPointRenderer().Reset();
    scene_manager_.GetTextRenderer().Reset();

    scene_object_adapters_.clear();
}

void ModelAdapter::AttachtToShellRenderer(ShellObject& shell_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<ShellAdapter>(new ShellAdapter(shell_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    ShellAdapter* shell_adapter_ptr = dynamic_cast<ShellAdapter*>(scene_object_adapter_ptr);
    scene_manager_.GetShellRenderer().AttachShellAdapter(shell_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelAdapter::AttachtToTextureShellRenderer(TextureShellObject& texture_shell_object)
{
    scene_object_adapters_.push_back(
        std::unique_ptr<TextureShellAdapter>(new TextureShellAdapter(texture_shell_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    TextureShellAdapter* texture_shell_adapter_ptr = dynamic_cast<TextureShellAdapter*>(scene_object_adapter_ptr);
    scene_manager_.GetTextureShellRenderer().AttachTextureShellAdapter(texture_shell_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelAdapter::AttachtToLineRenderer(LineObject& line_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<LineAdapter>(new LineAdapter(line_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    LineAdapter* line_adapter_ptr = dynamic_cast<LineAdapter*>(scene_object_adapter_ptr);
    scene_manager_.GetLineRenderer().AttachLineAdapter(line_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelAdapter::AttachtToPointRenderer(PointObject& point_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<PointAdapter>(new PointAdapter(point_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    PointAdapter* point_adapter_ptr = dynamic_cast<PointAdapter*>(scene_object_adapter_ptr);
    scene_manager_.GetPointRenderer().AttachPointAdapter(point_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelAdapter::AttachtToTextRenderer(TextObject& text_object)
{
    scene_object_adapters_.push_back(std::unique_ptr<TextAdapter>(new TextAdapter(text_object)));
    SceneObjectAdapter* scene_object_adapter_ptr = scene_object_adapters_.back().get();

    TextAdapter* text_adapter_ptr = dynamic_cast<TextAdapter*>(scene_object_adapter_ptr);
    scene_manager_.GetTextRenderer().AttachTextAdapter(text_adapter_ptr);

    AttachtToSelectionRenderer(scene_object_adapter_ptr);
}

void ModelAdapter::AttachtToSelectionRenderer(SceneObjectAdapter* scene_object_adapter_ptr)
{
    scene_manager_.GetSelectionRenderer().AttachSceneObjectAdapter(scene_object_adapter_ptr);
}

void ModelAdapter::DetachFromShellRenderer(ShellObject& shell_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == shell_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            ShellAdapter* shell_adapter_ptr = dynamic_cast<ShellAdapter*>(scene_object_adapter_ptr);
            scene_manager_.GetShellRenderer().DetachShellAdapter(shell_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelAdapter::DetachFromTextureShellRenderer(TextureShellObject& texture_shell_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == texture_shell_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            TextureShellAdapter* texture_shell_adapter_ptr =
                dynamic_cast<TextureShellAdapter*>(scene_object_adapter_ptr);
            scene_manager_.GetTextureShellRenderer().DetachTextureShellAdapter(texture_shell_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelAdapter::DetachFromLineRenderer(LineObject& line_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == line_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            LineAdapter* line_adapter_ptr = dynamic_cast<LineAdapter*>(scene_object_adapter_ptr);
            scene_manager_.GetLineRenderer().DetachLineAdapter(line_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelAdapter::DetachFromPointRenderer(PointObject& point_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == point_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            PointAdapter* point_adapter_ptr = dynamic_cast<PointAdapter*>(scene_object_adapter_ptr);
            scene_manager_.GetPointRenderer().DetachPointAdapter(point_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelAdapter::DetachFromTextRenderer(TextObject& text_object)
{
    for(auto it = scene_object_adapters_.begin(); it != scene_object_adapters_.end(); ++it)
    {
        if((*it)->GetKey() == text_object.GetKey())
        {
            SceneObjectAdapter* scene_object_adapter_ptr = (*it).get();
            DetachFromSelectionRenderer(scene_object_adapter_ptr);

            TextAdapter* text_adapter_ptr = dynamic_cast<TextAdapter*>(scene_object_adapter_ptr);
            scene_manager_.GetTextRenderer().DetachTextAdapter(text_adapter_ptr);

            scene_object_adapters_.erase(it);
            break;
        }
    }
}

void ModelAdapter::DetachFromSelectionRenderer(SceneObjectAdapter* scene_object_adapter_ptr)
{
    scene_manager_.GetSelectionRenderer().DetachSceneObjectAdapter(scene_object_adapter_ptr);
}