#include "model_handler.hpp"

#include "utility/custom_exp.hpp"

ModelHandler::ModelHandler(const std::string & model_name):
	model(nullptr)
{
	model.reset(new Model(model_name));
}


ModelHandler::~ModelHandler(){

}

Model & ModelHandler::GetModel() const {
	return *model;
}

int ModelHandler::GenerateSceneObject(SceneObject * parent, std::string name, int priority){
	std::unique_ptr<SceneObject> scene_object(new SceneObject(parent, name, priority));
	int key = model->InsertSceneObject(scene_object);
	return key;
}

int ModelHandler::GenerateShellObject(SceneObject * parent, std::string name, int priority){
	std::unique_ptr<SceneObject> scene_object(new ShellObject(parent, name, priority));
	int key = model->InsertSceneObject(scene_object);
	return key;
}

int ModelHandler::GenerateTextureShellObject(SceneObject * parent, std::string name, int priority){
	std::unique_ptr<SceneObject> scene_object(new TextureShellObject(parent, name, priority));
	int key = model->InsertSceneObject(scene_object);
	return key;
}

int ModelHandler::GenerateLineObject(SceneObject * parent, std::string name, int priority){
	std::unique_ptr<SceneObject> scene_object(new LineObject(parent, name, priority));
	int key = model->InsertSceneObject(scene_object);
	return key;
}

int ModelHandler::GeneratePointObject(SceneObject * parent, std::string name, int priority){
	std::unique_ptr<SceneObject> scene_object(new PointObject(parent, name, priority));
	int key = model->InsertSceneObject(scene_object);
	return key;
}

int ModelHandler::GenerateTextObject(SceneObject * parent, std::string name, int priority){
	std::unique_ptr<SceneObject> scene_object(new TextObject(parent, name, priority));
	int key = model->InsertSceneObject(scene_object);
	return key;
}

SceneObject & ModelHandler::GetSceneObject(int id) const {
	SceneObject * scene_object_ptr =  model->GetSceneObject(id);
	return *scene_object_ptr;
}

ShellObject & ModelHandler::GetShellObject(int id) const {
	SceneObject * scene_object_ptr =  model->GetSceneObject(id);
	if(ShellObject * shell_object_ptr = dynamic_cast<ShellObject *>(scene_object_ptr)){
		return *shell_object_ptr;
	}
    std::string error("*** S3DR error: wrong ShellObject key.");
    throw CustomExp(error);
}

TextureShellObject & ModelHandler::GetTextureShellObject(int id) const {
	SceneObject * scene_object_ptr =  model->GetSceneObject(id);
	if(TextureShellObject * shell_object_ptr = dynamic_cast<TextureShellObject *>(scene_object_ptr)){
		return *shell_object_ptr;
	}
    std::string error("*** S3DR error: wrong TextureShellObject key.");
    throw CustomExp(error);
}

LineObject & ModelHandler::GetLineObject(int id) const {
	SceneObject * scene_object_ptr =  model->GetSceneObject(id);
	if(LineObject * line_object_ptr = dynamic_cast<LineObject *>(scene_object_ptr)){
		return *line_object_ptr;
	}
    std::string error("*** S3DR error: wrong LineObject key.");
    throw CustomExp(error);
}

PointObject & ModelHandler::GetPointObject(int id) const {
	SceneObject * scene_object_ptr =  model->GetSceneObject(id);
	if(PointObject * point_object_ptr = dynamic_cast<PointObject *>(scene_object_ptr)){
		return *point_object_ptr;
	}
    std::string error("*** S3DR error: wrong PointObject key.");
    throw CustomExp(error);
}

TextObject & ModelHandler::GetTextObject(int id) const {
	SceneObject * scene_object_ptr =  model->GetSceneObject(id);
	if(TextObject * text_object_ptr = dynamic_cast<TextObject *>(scene_object_ptr)){
		return *text_object_ptr;
	}
    std::string error("*** S3DR error: wrong TextObject key.");
    throw CustomExp(error);	
}