#include "model_manager.hpp"

#include "utility/custom_exp.hpp"

ModelManager::ModelManager(Model& model) : model_ptr(nullptr), model_ref(model)
{
}

ModelManager::ModelManager(const std::string& model_name) : model_ptr(new Model(model_name)), model_ref(*model_ptr)
{
}

ModelManager::~ModelManager()
{
}

Model& ModelManager::GetModel() const
{
    return model_ref;
}

int ModelManager::GenerateSceneObject(SceneObject* parent, std::string name, int priority)
{
    std::unique_ptr<SceneObject> scene_object(new SceneObject(parent, name, priority));
    int key = model_ref.AddSceneObject(scene_object);
    return key;
}

int ModelManager::GenerateMaterialShellObject(SceneObject* parent, std::string name, int priority)
{
    std::unique_ptr<SceneObject> scene_object(new MaterialShellObject(parent, name, priority));
    int key = model_ref.AddSceneObject(scene_object);
    return key;
}

int ModelManager::GenerateTextureShellObject(SceneObject* parent, std::string name, int priority)
{
    std::unique_ptr<SceneObject> scene_object(new TextureShellObject(parent, name, priority));
    int key = model_ref.AddSceneObject(scene_object);
    return key;
}

int ModelManager::GenerateLineObject(SceneObject* parent, std::string name, int priority)
{
    std::unique_ptr<SceneObject> scene_object(new LineObject(parent, name, priority));
    int key = model_ref.AddSceneObject(scene_object);
    return key;
}

int ModelManager::GeneratePointObject(SceneObject* parent, std::string name, int priority)
{
    std::unique_ptr<SceneObject> scene_object(new PointObject(parent, name, priority));
    int key = model_ref.AddSceneObject(scene_object);
    return key;
}

int ModelManager::GenerateTextObject(SceneObject* parent, std::string name, int priority)
{
    std::unique_ptr<SceneObject> scene_object(new TextObject(parent, name, priority));
    int key = model_ref.AddSceneObject(scene_object);
    return key;
}

SceneObject& ModelManager::GetSceneObject(int id) const
{
    SceneObject* scene_object_ptr = model_ref.GetSceneObject(id);
    return *scene_object_ptr;
}

MaterialShellObject& ModelManager::GetMaterialShellObject(int id) const
{
    SceneObject* scene_object_ptr = model_ref.GetSceneObject(id);
    if(MaterialShellObject* shell_object_ptr = dynamic_cast<MaterialShellObject*>(scene_object_ptr))
    {
        return *shell_object_ptr;
    }
    std::string error("*** S3DR error: wrong ShellObject key.");
    throw CustomExp(error);
}

TextureShellObject& ModelManager::GetTextureShellObject(int id) const
{
    SceneObject* scene_object_ptr = model_ref.GetSceneObject(id);
    if(TextureShellObject* shell_object_ptr = dynamic_cast<TextureShellObject*>(scene_object_ptr))
    {
        return *shell_object_ptr;
    }
    std::string error("*** S3DR error: wrong TextureShellObject key.");
    throw CustomExp(error);
}

LineObject& ModelManager::GetLineObject(int id) const
{
    SceneObject* scene_object_ptr = model_ref.GetSceneObject(id);
    if(LineObject* line_object_ptr = dynamic_cast<LineObject*>(scene_object_ptr))
    {
        return *line_object_ptr;
    }
    std::string error("*** S3DR error: wrong LineObject key.");
    throw CustomExp(error);
}

PointObject& ModelManager::GetPointObject(int id) const
{
    SceneObject* scene_object_ptr = model_ref.GetSceneObject(id);
    if(PointObject* point_object_ptr = dynamic_cast<PointObject*>(scene_object_ptr))
    {
        return *point_object_ptr;
    }
    std::string error("*** S3DR error: wrong PointObject key.");
    throw CustomExp(error);
}

TextObject& ModelManager::GetTextObject(int id) const
{
    SceneObject* scene_object_ptr = model_ref.GetSceneObject(id);
    if(TextObject* text_object_ptr = dynamic_cast<TextObject*>(scene_object_ptr))
    {
        return *text_object_ptr;
    }
    std::string error("*** S3DR error: wrong TextObject key.");
    throw CustomExp(error);
}