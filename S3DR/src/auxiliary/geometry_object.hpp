#ifndef _GEOMETRY_OBJECT_H_
#define _GEOMETRY_OBJECT_H_

#include "utility/subject.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class GeometryObjectEvents : unsigned int { TRANSFORMATION_MATRIX_CHANGED, };

class GeometryObject: public Subject<GeometryObjectEvents> {
    public:
        GeometryObject();
        GeometryObject(const GeometryObject &)=delete;
        GeometryObject & operator=(const GeometryObject &)=delete;
        virtual ~GeometryObject();

        void SetPosition(const glm::vec3 & position);
        void SetTransformMatrix(const glm::mat4 &  transformation_matrix);

        const glm::vec3 & GetPosition() const;
        const glm::mat4 & GetTransformMatrix() const;

        void Translate(const glm::vec3 & vector);
        void Scale(const glm::vec3 & scale_coef);
        void Rotate(const glm::vec3 & axis, float angle_in_deg);

    private:
    	glm::vec3 position;
		glm::vec3 scale;
		glm::fquat orientation;

		glm::vec3 axis[3];
		
		glm::mat4 transformation_matrix;
};

#endif
