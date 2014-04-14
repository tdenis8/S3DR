#include "scene_object.hpp"

#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject(SceneObject * parent,  std::string name, int priority):
    Subject(),
    Observer(),
    GeometryObject(),
    parent(parent),
    key(-1),
    name(name),
    priority(priority),
    combine_model_matrix(glm::mat4(1.0)),
    object_options(0)
{
    if(priority < 0){
        priority = 0;
    }
    else if(priority > 2){
        priority = 2;
    }

    if(parent != nullptr){
        parent->Observe(SceneObjectEvents::COMBINED_MODEL_MATRIX_CHANGE, 
                        std::bind(&SceneObject::ParentModelMatrixChange, this, std::placeholders::_1),
                        this);
    }
}

SceneObject::~SceneObject(){
    if(parent != nullptr){
        parent->RemoveObservers(this);
    }
}

void SceneObject::ParentModelMatrixChange(const EventInfo & info){
    combine_model_matrix = parent->GetCombineModelMatrix() * GetModelMatrix();
    Emit(SceneObjectEvents::COMBINED_MODEL_MATRIX_CHANGE);
}

void SceneObject::CalculateModelMatrix(){
    GeometryObject::CalculateModelMatrix();
    ParentModelMatrixChange(EventInfo());
}

void SceneObject::SetKey(int key){
    this->key = key;
}

int SceneObject::GetKey() const {
    return key;
}

std::string SceneObject::GetName() const { 
    return name; 
}

int SceneObject::GetPriority() const {
    return priority;
}

const glm::mat4 & SceneObject::GetCombineModelMatrix() const{
    return combine_model_matrix;
}

void SceneObject::SetObjectOption(unsigned int option){
    object_options |= 1 << option;
}

void SceneObject::ResetObjectOption(unsigned int option){
    object_options &= 1 << option;
}

bool SceneObject::TestObjectOption(unsigned int option){
    return object_options & 1 << option;
}

unsigned int SceneObject::GetObjectOptions(){
    return object_options;
}

