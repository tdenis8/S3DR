#ifndef _LINE_ADAPTER_HPP_
#define _LINE_ADAPTER_HPP_

#include "model/line_object.hpp"
#include "scene_object_adapter.hpp"

class LineAdapter : public SceneObjectAdapter
{
    public:
    LineAdapter() = delete;
    LineAdapter(LineObject& line_object);
    LineAdapter(const LineAdapter&) = delete;
    LineAdapter& operator=(const LineAdapter&) = delete;
    ~LineAdapter();

    void Render();
    void SelectionRender(std::function<void(int)> set_scene_object_key, std::function<void(int)> set_entry_index);

    private:
    void UpdateData();

    LineObject& line_object_;

    GLuint vao_object_;
    GLuint vbo_objects_[3];
};

#endif