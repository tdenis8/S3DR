#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "misc/subject.hpp"

#include <memory>
#include <stack>
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
        
        SceneObject * SceneObjectPtr() const { 
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

        int InsertSceneObject(const std::shared_ptr<SceneObject> & scene_object);
        void RemoveSceneObject(const std::shared_ptr<SceneObject> & scene_object);

        void Reset();

        std::vector<SceneObject *> SceneObjects();
        SceneObject * SceneObjectPtr(int key);

        const std::string & Name() const;

    private:
        unsigned int id_counter;
        std::string name;
        std::vector<std::shared_ptr<SceneObject>> scene_objects;
};

#endif
