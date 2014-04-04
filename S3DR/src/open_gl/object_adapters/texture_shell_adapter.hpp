#ifndef _TEXTURE_SHELL_ADAPTER_HPP_
#define _TEXTURE_SHELL_ADAPTER_HPP_

#include "model/texture_shell_object.hpp"
#include "scene_object_adapter.hpp"

#include <vector>

class Texture;

class TextureShellAdapter: public SceneObjectAdapter {
	public:
		TextureShellAdapter()=delete;
		TextureShellAdapter(TextureShellObject * texture_shell_object);
		TextureShellAdapter(const TextureShellAdapter &)=delete;
		virtual ~TextureShellAdapter();

		void Render();
		void SelectionRender(std::function<void(int)> set_scene_object_key,
                             std::function<void(int)> set_entry_index);
		
	private:
		void UpdateData();

		TextureShellObject * texture_shell_object;
		bool allow_render;	
		GLuint vao_object;
		GLuint vbo_objects[4];

		std::vector<Texture> textures;
};

#endif