#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "auxiliary/geometry_object.hpp"

enum class LightType : unsigned int
{
    DIRECTIONAL,
    POINT,
    // SPOTLIGHT
};

class Light : public GeometryObject
{
    public:
    Light(LightType light_type);
    Light(const Light&) = delete;
    Light& operator=(const Light&) = delete;
    virtual ~Light();

    // Common to all light types
    void SetAmbientColor(const glm::vec3& ambient_color);
    void SetDiffuseColor(const glm::vec3& diffuse_color);
    void SetSpecularColor(const glm::vec3& specular_color);
    const glm::vec3& GetAmbientColor() const;
    const glm::vec3& GetDiffuseColor() const;
    const glm::vec3& GetSpecularColor() const;

    // Only directional and spotlight lights
    void SetLightDirection(const glm::vec3& direction);
    const glm::vec3& GetLightDirection() const;

    // Only point and spotlight lights
    void SetLightPositon(const glm::vec3& position);
    const glm::vec3& GetLightPosition() const;

    private:
    LightType light_type_;

    glm::vec3 ambient_color_;
    glm::vec3 diffuse_color_;
    glm::vec3 specular_color_;

    glm::vec3 direction_;
    glm::vec3 position_;
};

#endif
