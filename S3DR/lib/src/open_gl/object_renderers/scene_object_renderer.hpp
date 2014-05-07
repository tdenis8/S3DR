#ifndef _SCENE_OBJECT_RENDERER_HPP_
#define _SCENE_OBJECT_RENDERER_HPP_

#include "misc/program.hpp"

#include <memory>

class SceneObjectAdapter;

class SceneObjectRenderer {
	public:
		SceneObjectRenderer();
		~SceneObjectRenderer();
		SceneObjectRenderer(const SceneObjectRenderer &)=delete;
		SceneObjectRenderer & operator=(const SceneObjectRenderer &)=delete;

		void ActivateProgram();
		void DeactivateProgram();

		Program & ProgramRef();

	protected:
		std::shared_ptr<Program> program;
};

#endif