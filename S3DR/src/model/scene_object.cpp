#include "scene_object.hpp"

#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject(SceneObject * parent,  std::string name, int priority):
    Subject(),
    Observer(),
    parent(parent),
    key(-1),
    name(name),
    priority(priority),
    object_options(0),
    model_matrix(glm::mat4(1.0)),
    parent_model_matrix(glm::mat4(1.0)),
    combine_model_matrix(glm::mat4(1.0))
{
    if(priority < 0){
        priority = 0;
    }
    else if(priority > 2){
        priority = 2;
    }

    if(parent != nullptr){
        parent->Observe(SceneObjectEvents::MODEL_MATRIX_CHANGED, 
                        std::bind(&SceneObject::ParentModelMatrixChanged, this, std::placeholders::_1),
                        this);
    }
}

SceneObject::~SceneObject(){
    if(parent != nullptr){
        parent->RemoveObservers(this);
    }
}

void SceneObject::SetKey(int key){
    this->key = key;
}

void SceneObject::CalculateModelMatrix(){
    combine_model_matrix = parent_model_matrix * model_matrix;
    Emit(SceneObjectEvents::MODEL_MATRIX_CHANGED);
}

void SceneObject::ParentModelMatrixChanged(const EventInfo & info){
    parent_model_matrix = parent->CombineModelMatrixRef();
    CalculateModelMatrix();
}

int SceneObject::Key() const {
    return key;
}

std::string SceneObject::Name() const { 
    return name; 
}

int SceneObject::Priority() const {
    return priority;
}

const glm::mat4 & SceneObject::ModelMatrixRef() const {
    return model_matrix;
}

const glm::mat4 & SceneObject::CombineModelMatrixRef() const{
    return combine_model_matrix;
}

void SceneObject::SetModelMatrix(const glm::mat4 & model_matrix){
    this->model_matrix = model_matrix;
    CalculateModelMatrix();
}

void SceneObject::Translate(const glm::vec3 & vector){
    model_matrix = glm::translate(model_matrix, vector);
    CalculateModelMatrix();
}

void SceneObject::Scale(const glm::vec3 & scale_coef){
    // model_matrix = glm::scale(model_matrix, scale_coef);
    model_matrix[0][0] = scale_coef.x;
    model_matrix[1][1] = scale_coef.y;
    model_matrix[2][2] = scale_coef.z;
    CalculateModelMatrix();
}

void SceneObject::Rotate(const glm::vec3 & axis, float angle_in_deg){
    model_matrix = glm::rotate(model_matrix, angle_in_deg, axis);
    CalculateModelMatrix();  
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