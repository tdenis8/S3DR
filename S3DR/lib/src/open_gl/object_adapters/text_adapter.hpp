#ifndef _TEXT_ADAPTER_HPP_
#define _TEXT_ADAPTER_HPP_

#include "model/text_object.hpp"
#include "scene_object_adapter.hpp"

class TextAdapter: public SceneObjectAdapter {
	public:
		TextAdapter()=delete;
		TextAdapter(TextObject * text_object);
		TextAdapter(const TextAdapter &)=delete;
		virtual ~TextAdapter();

		void Render();
		void SelectionRender(std::function<void(int)> set_scene_object_key,
                             std::function<void(int)> set_entry_index);
		
	private:
		void UpdateData();

		TextObject * text_object;
		
		GLuint vao_object;
		GLuint vbo_objects[3];
};

#endif