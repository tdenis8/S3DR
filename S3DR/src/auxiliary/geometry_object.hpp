#ifndef _GEOMETRY_OBJECT_H_
#define _GEOMETRY_OBJECT_H_

#include "utility/subject.hpp"
#include <glm/glm.hpp>

enum class GeometryObjectEvents : unsigned int { TRANSFORMATION_MATRIX_CHANGED, };

class GeometryObject: public Subject<GeometryObjectEvents> {
    public:
        GeometryObject();
        GeometryObject(const GeometryObject &)=delete;
        GeometryObject & operator=(const GeometryObject &)=delete;
        virtual ~GeometryObject();

    private:
    	glm::mat4 transformation_matrix;
};

#endif
