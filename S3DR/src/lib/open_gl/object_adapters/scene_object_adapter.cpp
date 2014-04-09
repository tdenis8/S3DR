#include "scene_object_adapter.hpp"

SceneObjectAdapter::SceneObjectAdapter(SceneObject * scene_object):
	scene_object(scene_object)
{
	auto id = scene_object->Observe(SceneObjectEvents::DATA_UPDATE,
							 	    std::bind(&SceneObjectAdapter::SceneObjectDataUpdate, this, std::placeholders::_1));
	observer_ids.push_back(id);
}

SceneObjectAdapter::~SceneObjectAdapter(){
	for(auto id: observer_ids){
		scene_object->RemoveObserver(id);
	}
}

void SceneObjectAdapter::SceneObjectDataUpdate(const EventInfo & info){
	UpdateData();
}

const glm::mat4 & SceneObjectAdapter::ModelMatrixRef() const{
    return scene_object->ModelMatrixRef();
}

int SceneObjectAdapter::Key() const{
	return scene_object->Key();
}

int SceneObjectAdapter::Priority() const{
    return scene_object->Priority();
}