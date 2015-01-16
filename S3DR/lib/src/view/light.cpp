#include "light.hpp"

Light::Light(LightType light_type)
   : light_type_(light_type)
{
}

Light::~Light()
{
}

void Light::SetAmbientColor(const glm::vec3& ambient_color)
{
   ambient_color_ = ambient_color;
}

void Light::SetDiffuseColor(const glm::vec3& diffuse_color)
{
   diffuse_color_ = diffuse_color;
}

void Light::SetSpecularColor(const glm::vec3& specular_color)
{
   specular_color_ = specular_color;
}

const glm::vec3& Light::GetAmbientColor() const
{
   return ambient_color_;
}

const glm::vec3& Light::GetDiffuseColor() const
{
   return diffuse_color_;
}

const glm::vec3& Light::GetSpecularColor() const
{
   return specular_color_;
}

void Light::SetLightDirection(const glm::vec3& direction)
{
   direction_ = direction;
}

const glm::vec3& Light::GetLightDirection() const
{
   return direction_;
}

void Light::SetLightPositon(const glm::vec3& position)
{
   position_ = position;
}

const glm::vec3& Light::GetLightPosition() const
{
   return position_;
}