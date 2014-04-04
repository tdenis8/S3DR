#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include <glm/glm.hpp>

enum class ProjectionType {Perspective, Orthogonal};

class Projection {
    public:
        Projection() = delete;
        Projection(float field_of_view, int window_width, int window_height, float near_plane, float far_plane);
        virtual ~Projection();
        Projection(const Projection &)=delete;
        Projection & operator=(const Projection &)=delete;

        const glm::mat4 & ProjectionMatrixRef() const;

        void SetProjectionType(ProjectionType projection_type);
		void SetAspectRatio(int window_width, int window_height);
		void ChangeFieldOfView(float delta);

        int Width() const;
        int Height() const;
        
    private:
    	void CalculateProjection();

		float field_of_view;
		int window_width;
		int window_height;
		float near_plane; 
		float far_plane;

    	glm::mat4 projection_matrix;
    	ProjectionType projection_type;
};

#endif