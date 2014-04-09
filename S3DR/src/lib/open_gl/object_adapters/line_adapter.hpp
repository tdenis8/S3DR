#ifndef _LINE_ADAPTER_HPP_
#define _LINE_ADAPTER_HPP_

#include "model/line_object.hpp"
#include "scene_object_adapter.hpp"

class LineAdapter: public SceneObjectAdapter {
	public:
		LineAdapter()=delete;
		LineAdapter(LineObject * line_object);
		LineAdapter(const LineAdapter &)=delete;
		virtual ~LineAdapter();

		void Render();
		void SelectionRender(std::function<void(int)> set_scene_object_key,
                             std::function<void(int)> set_entry_index);
		
	private:
		void UpdateData();

		LineObject * line_object;
		
		GLuint vao_object;
		GLuint vbo_objects[3];
};

#endif