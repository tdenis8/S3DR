#ifndef _POINT_ADAPTER_HPP_
#define _POINT_ADAPTER_HPP_

#include "model/point_object.hpp"
#include "scene_object_adapter.hpp"

class PointAdapter : public SceneObjectAdapter
{
    public:
    PointAdapter() = delete;
    PointAdapter(PointObject& point_object);
    PointAdapter(const PointAdapter&) = delete;
    PointAdapter& operator=(const PointAdapter&) = delete;
    ~PointAdapter();

    void Render();
    void SelectionRender(std::function<void(int)> set_scene_object_key, std::function<void(int)> set_entry_index);

    private:
    void UpdateData();

    PointObject& point_object_;

    GLuint vao_object_;
    GLuint vbo_objects_[3];
};

#endif