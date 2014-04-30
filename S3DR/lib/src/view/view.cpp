#include "view.hpp"

#include "utility/custom_exp.hpp"

#include "model/model.hpp"
#include "open_gl/open_gl_view_adapter.hpp"
#include "operator/operator.hpp"
#include "camera.hpp"
#include "projection.hpp"
#include "selection_set.hpp"

View::View():
	Subject(),
	MouseEventsDispatcher(),
	KeyboardEventsDispatcher(),
	camera(nullptr),
	projection(nullptr),
	selection_set(nullptr),
	view_adapter(nullptr),
	model(nullptr),
	opr(nullptr)
{
	try{
		selection_set.reset(new SelectionSet());
		view_adapter.reset(new OpenGLViewAdapter(*this));
	}
    catch(CustomExp e){
        throw e;
    }

	camera.reset(new Camera(glm::vec3(0.0f, 0.0f, 15.0f),
							glm::vec3(0.0, 0.0, -1.0),
							glm::vec3(0.0, 1.0, 0.0)));

	projection.reset(new Projection(15.0f, 800, 600, -0.1f, 100.0f));
	
	// Inform observers to set default width and height
    Emit(ViewEvent::WINDOW_RESIZE, WindowResizeInfo(800, 600));
	// Inform observers to apply all viewer settings
    Emit(ViewEvent::VIEWER_SETTINGS_CHANGE);
}

View::~View(){

}

Camera & View::CameraRef() {
	return (*camera.get());
}

Projection & View::ProjectionRef() {
	return (*projection.get());
}

const ViewSettings & View::ViewSettingsRef() const {
	return view_settings;
}

void View::AttachModel(Model * model){
	if(model == nullptr){
		return;
	}	
	if(this->model != nullptr){
		DetachModel();
	}
	this->model = model;
	Emit(ViewEvent::ATTACH_MODEL, AttachModelInfo(*model));	
}

void View::DetachModel(){
	if(model != nullptr){
		model = nullptr;
	}
	Emit(ViewEvent::DETACH_MODEL);
}

Model * View::ModelPtr(){
	return model;
}

void View::AttachOperator(Operator * opr){
	this->opr = opr;
	MouseEventsDispatcher::AttachOperator(opr);
	KeyboardEventsDispatcher::AttachOperator(opr);
}

void View::DetachOperator(){
	this->opr = nullptr;
	MouseEventsDispatcher::DetachOperator();
	KeyboardEventsDispatcher::DetachOperator();
}

Operator * View::OperatorPtr(){
	return opr;
}

void View::Redraw(){
	if(view_adapter){
		view_adapter->Render(camera->CameraMatrixRef(),
						 	 projection->ProjectionMatrixRef());
	}
}

void View::WindowResize(int width, int height){
	projection->SetAspectRatio(width, height);
	Emit(ViewEvent::WINDOW_RESIZE, WindowResizeInfo(width, height));
}

void View::SetBackgroundColor(const glm::vec3 & background_color){
	view_settings.background_color = background_color;
	Emit(ViewEvent::VIEWER_SETTINGS_CHANGE);
}

SelectionSet & View::SelectionSetRef(){
	return *selection_set;
}

float View::ScreenDepthAt(int x, int y) const{
	return view_adapter->ScreenDepthAt(x, y);
}