#include "model.hpp"

#include "scene_object.hpp"

Model::Model(const std::string & name):
    Subject(),
    id_counter(0),
    name(name)
{

}

Model::~Model() {

}

int Model::InsertSceneObject(const std::shared_ptr<SceneObject> & scene_object){ 
    int key = id_counter++;
    scene_object->SetKey(key);
    scene_objects.push_back(scene_object);
    Emit(ModelEvents::NEW_SCENE_OBJECT, SceneObjectInfo(scene_object.get()));
    return key;
}

void Model::RemoveSceneObject(const std::shared_ptr<SceneObject> & scene_object){
    if(!scene_object){
        return;
    }
    for(auto it=scene_objects.begin(); it!=scene_objects.end(); ++it){
        if((*it)->Key() == scene_object->Key()){
            Emit(ModelEvents::REMOVE_SCENE_OBJECT, SceneObjectInfo(scene_object.get()));
            scene_objects.erase(it);
            break;
        }
    }
}

void Model::Reset(){
    Emit(ModelEvents::RESET_MODEL);
    scene_objects.clear();
}
        
std::vector<SceneObject *> Model::SceneObjects(){
    std::vector<SceneObject *> rv;

    for(auto & scene_object_sptr: scene_objects){
        rv.push_back(scene_object_sptr.get());
    }

    return rv;
}

SceneObject * Model::SceneObjectPtr(int key){
    for(auto & scene_object_sptr: scene_objects){
        if(scene_object_sptr->Key() == key){
            return scene_object_sptr.get();
        }
    }
    return nullptr;
}

const std::string & Model::Name() const {
    return name;
}