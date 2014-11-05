#ifndef _MODEL_HANDLER_HPP_
#define _MODEL_HANDLER_HPP_

#include "model.hpp"
#include "scene_object.hpp"
#include "shell_object.hpp"
#include "texture_shell_object.hpp"
#include "line_object.hpp"
#include "point_object.hpp"
#include "text_object.hpp"

#include <string>
#include <memory>

class ModelHandler
{
    public:
    ModelHandler() = delete;
    ModelHandler(Model& model);
    ModelHandler(const std::string& model_name);
    ModelHandler(const ModelHandler&) = delete;
    ModelHandler& operator=(const ModelHandler&) = delete;
    ~ModelHandler();

    Model& GetModel() const;

    // Plane SceneObjects are useful and efficient way to grouping other scene objects
    // (objects interherd from SceneObjects)
    int GenerateSceneObject(SceneObject* parent, std::string name, int priority = 1);
    int GenerateShellObject(SceneObject* parent, std::string name, int priority = 1);
    int GenerateTextureShellObject(SceneObject* parent, std::string name, int priority = 1);
    int GenerateLineObject(SceneObject* parent, std::string name, int priority = 1);
    int GeneratePointObject(SceneObject* parent, std::string name, int priority = 1);
    int GenerateTextObject(SceneObject* parent, std::string name, int priority = 1);

    SceneObject& GetSceneObject(int id) const;
    ShellObject& GetShellObject(int id) const;
    TextureShellObject& GetTextureShellObject(int id) const;
    LineObject& GetLineObject(int id) const;
    PointObject& GetPointObject(int id) const;
    TextObject& GetTextObject(int id) const;

    private:
    std::unique_ptr<Model> model_ptr;
    Model& model_ref;
};

#endif