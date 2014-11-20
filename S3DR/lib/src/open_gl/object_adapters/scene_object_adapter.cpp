#include "scene_object_adapter.hpp"

SceneObjectAdapter::SceneObjectAdapter(SceneObject& scene_object) : Observer(), scene_object_(scene_object)
{
    scene_object_.Observe(SceneObjectEvents::DATA_UPDATE,
                          std::bind(&SceneObjectAdapter::SceneObjectDataUpdate, this, std::placeholders::_1),
                          this);
}

SceneObjectAdapter::~SceneObjectAdapter()
{
    scene_object_.RemoveObservers(this);
}

void SceneObjectAdapter::SceneObjectDataUpdate(const EventInfo& info)
{
    UpdateData();
}

const glm::mat4& SceneObjectAdapter::GetModelMatrix() const
{
    return scene_object_.GetModelMatrix();
}

int SceneObjectAdapter::GetKey() const
{
    return scene_object_.GetKey();
}

int SceneObjectAdapter::GetPriority() const
{
    return scene_object_.GetPriority();
}