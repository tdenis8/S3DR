#include "open_gl_view_adapter.hpp"

#include "utility/custom_exp.hpp"

#include "view/view.hpp"
#include "view/selection_set.hpp"
#include "scene_settings.hpp"
#include "scene_manager.hpp"
#include "model_adapter.hpp"

OpenGLViewAdapter::OpenGLViewAdapter(View & view):
	ViewAdapter(view),
	selection_set(view.SelectionSetRef()),
	scene_settings(nullptr),
	scene_manager(nullptr),
	model_adapter(nullptr)
{
	try{
		scene_settings.reset(new SceneSettings());
		scene_manager.reset(new SceneManager(*scene_settings));
	}
    catch(CustomExp e){
        throw e;
    }

	auto id = view.Observe(ViewEvent::ATTACH_MODEL, 
							std::bind(&OpenGLViewAdapter::AttachModel, this, std::placeholders::_1));
	view_observer_ids.push_back(id);

	id = view.Observe(ViewEvent::DETACH_MODEL, 
					   std::bind(&OpenGLViewAdapter::DetachModel, this, std::placeholders::_1));
	view_observer_ids.push_back(id);

	id = view.Observe(ViewEvent::WINDOW_RESIZE, 
					   std::bind(&OpenGLViewAdapter::WindowResize, this, std::placeholders::_1));
	view_observer_ids.push_back(id);


	// View settings changes
	id = view.Observe(ViewEvent::VIEWER_SETTINGS_CHANGE,
					   std::bind(&OpenGLViewAdapter::ViewerSettingsChange, this, std::placeholders::_1));
	view_observer_ids.push_back(id);

	// Selections
	id = selection_set.Observe(SelectionSetEvent::CALCULATE_SELECTION, 
	  				   std::bind(&OpenGLViewAdapter::CalculateSelection, this, std::placeholders::_1));

	selection_set_observer_ids.push_back(id);
}

OpenGLViewAdapter::~OpenGLViewAdapter(){
	for(auto id: view_observer_ids){
		view.RemoveObserver(id);
	}

	for(auto id: selection_set_observer_ids){
		selection_set.RemoveObserver(id);
	}
}


void OpenGLViewAdapter::AttachModel(const EventInfo & info){
	const AttachModelInfo & am_info = dynamic_cast<const AttachModelInfo &>(info);
	model_adapter.reset(new ModelAdapter(am_info.ModelRef(), *scene_manager));
}

void OpenGLViewAdapter::DetachModel(const EventInfo & info){
	ModelAdapter * ptr = model_adapter.release();
	if(ptr == nullptr){
		return;
	}
	delete ptr;
}

void OpenGLViewAdapter::WindowResize(const EventInfo & info){
	const WindowResizeInfo & wr_info = dynamic_cast<const WindowResizeInfo &>(info);
	scene_settings->SetWidthHeight(wr_info.Width(), wr_info.Height());
}

void OpenGLViewAdapter::ViewerSettingsChange(const EventInfo & info){
	scene_settings->SetBackgroundColor(ViewSettingsRef().background_color);
}

void OpenGLViewAdapter::CalculateSelection(const EventInfo & info){
	if(!model_adapter){
		return;
	}

	const SelectionInfo & s_info = dynamic_cast<const SelectionInfo &>(info);
	scene_manager->SelectionRender();
	SelectionTexture & selection_texture = scene_manager->SelectionTextureRef();
	selection_set.SetSelectionData(selection_texture.GetSelectionData(s_info.X(), s_info.Y()));
}


void OpenGLViewAdapter::Render(const glm::mat4 & view_matrix, const glm::mat4 & projection_matrix){
	if(model_adapter){
		scene_manager->Render(view_matrix, projection_matrix);
	}
}

float OpenGLViewAdapter::ScreenDepthAt(int x, int y) const{
	return scene_manager->ScreenDepthAt(x, y);
}