#include "scene_manager.hpp"

#include "utility/custom_exp.hpp"

#include "scene_settings.hpp"

#include <glm/gtc/type_ptr.hpp>


SceneManager::SceneManager(SceneSettings & scene_settings):
	scene_settings(scene_settings),
	lights_UBO(-1),
	shell_renderer(nullptr),
	texture_shell_renderer(nullptr),
	transparency_renderer(nullptr),
	line_renderer(nullptr),
	point_renderer(nullptr),
	selection_renderer(nullptr),
	selection_texture(nullptr)
{
	try{
		InitOpenGL();
		InitUBOs();
		shell_renderer.reset(new ShellRenderer());
		texture_shell_renderer.reset(new TextureShellRenderer());
		transparency_renderer.reset(new TransparencyRenderer());
		line_renderer.reset(new LineRenderer());
		point_renderer.reset(new PointRenderer());
		selection_renderer.reset(new SelectionRenderer());
		selection_texture.reset(new SelectionTexture());
		ConnectUBOsAndPrograms();
	}
    catch(CustomExp e){
        throw e;
    }

    // Set initial settings
    LightsChanged(EventInfo());

    // Set observers
    int id = scene_settings.Observe(SceneSettingsEvents::WIDTH_HEIGHT_CHANGED, 
                                    std::bind(&SceneManager::WidthHeightChanged, this, std::placeholders::_1));
    observer_ids.push_back(id);

    id = scene_settings.Observe(SceneSettingsEvents::BACKGROUND_COLOR_CHANGED, 
                                    std::bind(&SceneManager::BackgroundColorChanged, this, std::placeholders::_1));
    observer_ids.push_back(id);

    id = scene_settings.Observe(SceneSettingsEvents::LIGHTS_CHANGED, 
                                std::bind(&SceneManager::LightsChanged, this, std::placeholders::_1));
    observer_ids.push_back(id);
}

SceneManager::~SceneManager(){
	for(auto id: observer_ids){
        scene_settings.RemoveObserver(id);
    }
	glDeleteBuffers(1, &lights_UBO);
}

void SceneManager::InitOpenGL(){
	glewExperimental = GL_TRUE;
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
	    std::string error = std::string("*** Failed to initialize GLEW");
	    throw CustomExp(error);
	}

	if(!GLEW_VERSION_3_3){
		std::string error("*** OpenGL 3.3 API is not available.");
	    throw CustomExp(error);
	}

	// Common settings
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SceneManager::InitUBOs(){
  	glGenBuffers(1, &lights_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lights_UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightsBlock), NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SceneManager::ConnectUBOsAndPrograms(){
	int lights_binding_index = 0;
	GLuint UBO_index = shell_renderer->ProgramRef().UniformBlock("LightsBlock");
  	glUniformBlockBinding(shell_renderer->ProgramRef().ProgramObject(), UBO_index, lights_binding_index);
  	glBindBufferRange(GL_UNIFORM_BUFFER, lights_binding_index, lights_UBO, 0, sizeof(LightsBlock));

  	// UBO_index = texture_shell_renderer->ProgramRef().UniformBlock("LightsBlock");
  	// glUniformBlockBinding(texture_shell_renderer->ProgramRef().ProgramObject(), UBO_index, lights_binding_index);
  	// glBindBufferRange(GL_UNIFORM_BUFFER, lights_binding_index, lights_UBO, 0, sizeof(LightsBlock));

  	// transparency_renderer->ActivateProgram(DDPPassType::PEEL);
  	// UBO_index = transparency_renderer->ProgramRef().UniformBlock("LightsBlock");
  	// glUniformBlockBinding(transparency_renderer->ProgramRef().ProgramObject(), UBO_index, lights_binding_index);
  	// glBindBufferRange(GL_UNIFORM_BUFFER, lights_binding_index, lights_UBO, 0, sizeof(LightsBlock));
}

void SceneManager::WidthHeightChanged(const EventInfo & info){
	transparency_renderer->SetWidthHeight(scene_settings.Width(), scene_settings.Height());
	selection_texture->SetWidthHeight(scene_settings.Width(), scene_settings.Height());
}

void SceneManager::BackgroundColorChanged(const EventInfo & info){
	transparency_renderer->SetBackgroundColor(glm::vec4(scene_settings.BackgroundColor(),0.0));
}

void SceneManager::LightsChanged(const EventInfo & info){
	UpdateLightsPositons();
}

void SceneManager::UpdateLightsPositons(){
	LightsBlock lights_block = scene_settings.LightsBlockInCameraSpace(view_matrix);

	glBindBuffer(GL_UNIFORM_BUFFER, lights_UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lights_block), &lights_block);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SceneManager::Render(const glm::mat4 & view, const glm::mat4 & projection){
	view_matrix = view;
	projection_matrix = projection;
	UpdateLightsPositons();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// // Priority 0 render
	// point_renderer->Render(view, projection, 0);
	// line_renderer->Render(view, projection, 0);
	// shell_renderer->Render(view, projection, 0);

	// Priority 1 render
	// glClear(GL_DEPTH_BUFFER_BIT);
	point_renderer->Render(view, projection, 1);
	line_renderer->Render(view, projection, 1);
	shell_renderer->Render(view, projection, 1);
	texture_shell_renderer->Render(view, projection, 1);
	transparency_renderer->Render(view_matrix, projection_matrix, 1);

	// // Priority 2 render
	// glClear(GL_DEPTH_BUFFER_BIT);
	// point_renderer->Render(view, projection, 2);
	// line_renderer->Render(view, projection, 2);
	// shell_renderer->Render(view, projection, 2);
}

void SceneManager::SelectionRender(){
	selection_texture->EnableWriting();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Priority 0 render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	selection_renderer->Render(view_matrix, projection_matrix, 0);
	// Priority 1 render
	glClear(GL_DEPTH_BUFFER_BIT);
	selection_renderer->Render(view_matrix, projection_matrix, 1);
	// Priority 2 render
	glClear(GL_DEPTH_BUFFER_BIT);
	selection_renderer->Render(view_matrix, projection_matrix, 2);

	selection_texture->DisableWriting();
	glm::vec3 background_color = scene_settings.BackgroundColor();
	glClearColor(background_color.x, background_color.y, background_color.z, 0.0f);
}

ShellRenderer & SceneManager::ShellRendererRef(){
	return *shell_renderer;
}

TextureShellRenderer & SceneManager::TextureShellRendererRef(){
	return *texture_shell_renderer;
}

TransparencyRenderer & SceneManager::TransparencyRendererRef(){
	return * transparency_renderer;
}

LineRenderer & SceneManager::LineRendererRef(){
	return * line_renderer;
}

PointRenderer & SceneManager::PointRendererRef(){
	return * point_renderer;
}

SelectionRenderer & SceneManager::SelectionRendererRef(){
	return * selection_renderer;
}

SelectionTexture & SceneManager::SelectionTextureRef(){
	return * selection_texture;
}

float SceneManager::ScreenDepthAt(int x, int y) const {
	float depth;
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glReadPixels(x, y-1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	return depth;
}