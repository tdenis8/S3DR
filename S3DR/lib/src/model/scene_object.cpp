#include "scene_object.hpp"

#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject(SceneObject* parent, std::string name, int priority)
    : Subject<SceneObjectEvents>::Subject()
    , Observer()
    , GeometryObject()
    , parent_(parent)
    , key_(-1)
    , name_(name)
    , priority_(priority)
    , combine_model_matrix_(glm::mat4(1.0))
    , object_options_(0)
{
    if(priority_ < 0)
    {
        priority_ = 0;
    }
    else if(priority_ > 2)
    {
        priority_ = 2;
    }

    if(parent != nullptr)
    {
        parent->Subject<SceneObjectEvents>::Observe(
            SceneObjectEvents::COMBINED_MODEL_MATRIX_CHANGE,
            std::bind(&SceneObject::ParentModelMatrixChange, this, std::placeholders::_1),
            this);
    }
}

SceneObject::~SceneObject()
{
    if(parent_ != nullptr)
    {
        parent_->Subject<SceneObjectEvents>::RemoveObservers(this);
    }
}

void SceneObject::ParentModelMatrixChange(const EventInfo& info)
{
    combine_model_matrix_ = parent_->GetCombineModelMatrix() * GetModelMatrix();
    Subject<SceneObjectEvents>::Emit(SceneObjectEvents::COMBINED_MODEL_MATRIX_CHANGE);
}

void SceneObject::CalculateModelMatrix()
{
    GeometryObject::CalculateModelMatrix();
    ParentModelMatrixChange(EventInfo());
}

void SceneObject::SetKey(int key)
{
    key_ = key;
}

int SceneObject::GetKey() const
{
    return key_;
}

std::string SceneObject::GetName() const
{
    return name_;
}

int SceneObject::GetPriority() const
{
    return priority_;
}

const glm::mat4& SceneObject::GetCombineModelMatrix() const
{
    return combine_model_matrix_;
}

void SceneObject::SetObjectOption(unsigned int option)
{
    object_options_ |= 1 << option;
}

void SceneObject::ResetObjectOption(unsigned int option)
{
    object_options_ &= 1 << option;
}

bool SceneObject::TestObjectOption(unsigned int option)
{
    return object_options_ & 1 << option;
}

unsigned int SceneObject::GetObjectOptions()
{
    return object_options_;
}
