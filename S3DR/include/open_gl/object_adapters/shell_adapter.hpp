#ifndef _SHELL_ADAPTER_HPP_
#define _SHELL_ADAPTER_HPP_

#include "model/shell_object.hpp"
#include "scene_object_adapter.hpp"

class ShellAdapter: public SceneObjectAdapter {
	public:
		ShellAdapter()=delete;
		ShellAdapter(ShellObject * shell_object);
		ShellAdapter(const ShellAdapter &)=delete;
		virtual ~ShellAdapter();

		void Render();
		void SelectionRender(std::function<void(int)> set_scene_object_key,
                             std::function<void(int)> set_entry_index);
		
		// TODO: optimize this
		const glm::vec4 & MaterialColor(){return shell_object->ShellMaterialRef().color;};
		int MaterialStatus(){return shell_object->ShellMaterialRef().status;};

	private:
		void UpdateData();

		ShellObject * shell_object;
		
		GLuint vao_object;
		GLuint vbo_objects[4];
};

#endif