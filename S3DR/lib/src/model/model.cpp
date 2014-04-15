#include "model.hpp"

#include "utility/custom_exp.hpp"

#include "scene_object.hpp"

Model::Model(const std::string & name):
    Subject(),
    id_counter(0),
    name(name)
{

}

Model::~Model() {
    Reset();
}

int Model::InsertSceneObject(std::unique_ptr<SceneObject> & scene_object){ 
    int key = id_counter++;
    scene_object->SetKey(key);
    scene_objects.push_back(std::move(scene_object));
    Emit(ModelEvents::NEW_SCENE_OBJECT, SceneObjectInfo(scene_object.get()));
    return key;
}

void Model::RemoveSceneObject(int key){
    for(auto it=scene_objects.begin(); it!=scene_objects.end(); ++it){
        if((*it)->GetKey() == key){
            Emit(ModelEvents::REMOVE_SCENE_OBJECT, SceneObjectInfo((*it).get()));
            scene_objects.erase(it);
            break;
        }
    }
}

void Model::Reset(){
    Emit(ModelEvents::RESET_MODEL);
    scene_objects.clear();
}
        
std::vector<SceneObject *> Model::GetSceneObjects(){
    std::vector<SceneObject *> rv;
    for(auto & scene_object_ptr: scene_objects){
        rv.push_back(scene_object_ptr.get());
    }
    return rv;
}

SceneObject * Model::GetSceneObject(int key){
    for(auto & scene_object_ptr: scene_objects){
        if(scene_object_ptr->GetKey() == key){
            return scene_object_ptr.get();
        }
    }
    std::string error("*** S3DR error: wrong SceneObject key.");
    throw CustomExp(error);
}

const std::string & Model::Name() const {
    return name;
}