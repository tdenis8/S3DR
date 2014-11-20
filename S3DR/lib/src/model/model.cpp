#include "model.hpp"

#include "utility/custom_exp.hpp"

#include "scene_object.hpp"

Model::Model(const std::string& name) : Subject(), id_counter_(0), name_(name)
{
}

Model::~Model()
{
    Reset();
}

int Model::InsertSceneObject(std::unique_ptr<SceneObject>& scene_object)
{
    int key = id_counter_++;
    scene_object->SetKey(key);
    scene_objects_.push_back(std::move(scene_object));
    Emit(ModelEvents::NEW_SCENE_OBJECT, SceneObjectInfo(scene_objects_.back().get()));
    return key;
}

void Model::RemoveSceneObject(int key)
{
    for(auto it = scene_objects_.begin(); it != scene_objects_.end(); ++it)
    {
        if((*it)->GetKey() == key)
        {
            Emit(ModelEvents::REMOVE_SCENE_OBJECT, SceneObjectInfo((*it).get()));
            scene_objects_.erase(it);
            break;
        }
    }
}

void Model::Reset()
{
    Emit(ModelEvents::RESET_MODEL);
    scene_objects_.clear();
}

std::vector<SceneObject*> Model::GetSceneObjects()
{
    std::vector<SceneObject*> rv;
    for(auto& scene_object_ptr : scene_objects_)
    {
        rv.push_back(scene_object_ptr.get());
    }
    return rv;
}

SceneObject* Model::GetSceneObject(int key)
{
    for(auto& scene_object_ptr : scene_objects_)
    {
        if(scene_object_ptr->GetKey() == key)
        {
            return scene_object_ptr.get();
        }
    }
    std::string error("*** S3DR error: wrong SceneObject key.");
    throw CustomExp(error);
}

const std::string& Model::GetName() const
{
    return name_;
}