#include "camera_operator.hpp"

#include "view/view.hpp"
#include "view/projection.hpp"
#include "view/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

CameraOperator::CameraOperator(View & view):
	Operator(view)
{

}

CameraOperator::~CameraOperator(){

}

int CameraOperator::OnLeftButtonDownAndMove(const MouseEventInfo & info){
	auto & camera = view.CameraRef();
	camera.RotateCamera(glm::vec3(1.0f, 0.0f, 0.0f), info.YDelta() / 10.0f);
	camera.RotateCamera(glm::vec3(0.0f, 1.0f, 0.0f), info.XDelta() / 10.0f);
	return 1;
}

int CameraOperator::OnRightButtonDownAndMove(const MouseEventInfo & info){
	auto & camera = view.CameraRef();
	camera.MoveCamera(info.XDelta()/10.0f, info.YDelta()/10.f);
	return 1;
}

#include <iostream>
int CameraOperator::OnMouseWheel(const MouseEventInfo & info){
	auto & projection = view.ProjectionRef();
	projection.ChangeFieldOfView(info.WheelDelta());
	

	// float width = projection.Width();
 // 	float height = projection.Height();

 // 	auto & camera = view.CameraRef();
 // 	std::cout<<"Mx: "<< ((width/2.0)-info.X())/20.0f<<std::endl;
 // 	std::cout<<"My: "<< ((height/2.0)-info.Y())/20.f<<std::endl;
	// camera.MoveCamera(-((width/2.0)-info.X())/20.0f, -((height/2.0)-info.Y())/20.f);

	return 1;
}

//Utility functions
glm::vec3 CameraOperator::MousePosition(const MouseEventInfo & info) const {
	auto & camera = view.CameraRef();
	auto & projection = view.ProjectionRef();
	float width = projection.Width();
    float height = projection.Height();

    int screen_x = info.X();
    int screen_y = info.Y();
    float screen_z = view.ScreenDepthAt(screen_x, screen_y);

    if(1-screen_z < 1e-7){
    	screen_z = 0.05;
    }

    glm::vec3 world_positon = glm::unProject(glm::vec3(screen_x, height-screen_y-1,  screen_z), 
    					  				     camera.CameraMatrixRef(), 
    					                     projection.ProjectionMatrixRef(), 
    					                     glm::vec4(0.0f, 0.0f, width, height));
    return world_positon;
}
