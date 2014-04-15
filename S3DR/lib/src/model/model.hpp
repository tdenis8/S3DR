#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "utility/subject.hpp"

#include <memory>
#include <vector>
#include <string>

// Forward declarations
class SceneObject;

enum class ModelEvents : unsigned int { NEW_SCENE_OBJECT,
                                        REMOVE_SCENE_OBJECT,
                                        RESET_MODEL };

class SceneObjectInfo: public EventInfo {
    public:
        SceneObjectInfo(SceneObject * object) : 
            EventInfo(), object(object) {}
        
        SceneObject * GetSceneObject() const { 
            return object;
        }

    private:
        SceneObject * object;
};


class Model: public Subject<ModelEvents> {
    public:
        Model()=delete;
        Model(const std::string & name);
        Model(const Model &)=delete;
        Model & operator=(const Model &)=delete;
        ~Model();

        // NOTE: this method move ownership of scene_object to model
        int InsertSceneObject(std::unique_ptr<SceneObject> & scene_object);
        void RemoveSceneObject(int key);

        void Reset();

        std::vector<SceneObject *> GetSceneObjects();
        SceneObject * GetSceneObject(int key);

        const std::string & Name() const;

    private:
        unsigned int id_counter;
        std::string name;
        std::vector<std::unique_ptr<SceneObject>> scene_objects;
};

#endif
