#ifndef _SCENE_OBJECT_ADAPTER_HPP_
#define _SCENE_OBJECT_ADAPTER_HPP_

#include "model/scene_object.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <functional>

class SceneObjectAdapter: public Observer {
    public:
        SceneObjectAdapter()=delete;
        SceneObjectAdapter(SceneObject & scene_object);
        SceneObjectAdapter(const SceneObjectAdapter &)=delete;
        SceneObjectAdapter & operator=(const SceneObjectAdapter &)=delete;
        virtual ~SceneObjectAdapter();

        const glm::mat4 & GetModelMatrix() const;
        int GetKey() const;
        int GetPriority() const;

        virtual void Render()=0;
        virtual void SelectionRender(std::function<void(int)> set_scene_object_key,
                                     std::function<void(int)> set_entry_index)=0;

    protected:
        virtual void UpdateData() = 0;

    private:
        void SceneObjectDataUpdate(const EventInfo & info);

        SceneObject & scene_object;
};

#endif