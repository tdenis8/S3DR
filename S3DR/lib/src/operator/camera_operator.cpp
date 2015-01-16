#include "camera_operator.hpp"

#include "view/view.hpp"
#include "view/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

CameraOperator::CameraOperator(View& view) : Operator(view)
{
}

CameraOperator::~CameraOperator()
{
}

int CameraOperator::OnLeftButtonDownAndMove(const MouseEventInfo& info)
{
   auto& camera = view.GetCamera();
   camera.RotateCamera(info.YDelta() / 10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
   camera.RotateCamera(info.XDelta() / 10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
   return 1;
}

int CameraOperator::OnRightButtonDownAndMove(const MouseEventInfo& info)
{
   auto& camera = view.GetCamera();
   camera.MoveCamera(info.XDelta() / 10.0f, info.YDelta() / 10.f);
   return 1;
}

#include <iostream>
int CameraOperator::OnMouseWheel(const MouseEventInfo& info)
{
   auto& camera = view.GetCamera();
   camera.ChangeFieldOfView(info.WheelDelta());

   // float width = projection.Width();
   //    float height = projection.Height();

   //    auto & camera = view.GetCamera();
   //    std::cout<<"Mx: "<< ((width/2.0)-info.X())/20.0f<<std::endl;
   //    std::cout<<"My: "<< ((height/2.0)-info.Y())/20.f<<std::endl;
   // camera.MoveCamera(-((width/2.0)-info.X())/20.0f, -((height/2.0)-info.Y())/20.f);

   return 1;
}

// Utility functions
glm::vec3 CameraOperator::MousePosition(const MouseEventInfo& info) const
{
   auto& camera = view.GetCamera();
   float width = camera.GetWidth();
   float height = camera.GetHeight();

   int screen_x = info.X();
   int screen_y = info.Y();
   float screen_z = view.ScreenDepthAt(screen_x, screen_y);

   if (1 - screen_z < 1e-7)
   {
      screen_z = 0.05;
   }

   glm::vec3 world_positon = glm::unProject(glm::vec3(screen_x, height - screen_y - 1, screen_z), camera.GetViewMatrix(),
                                            camera.GetProjectionMatrix(), glm::vec4(0.0f, 0.0f, width, height));
   return world_positon;
}
