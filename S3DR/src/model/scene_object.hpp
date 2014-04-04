#ifndef _SCENE_OBJECT_H_
#define _SCENE_OBJECT_H_

#include "misc/subject.hpp"
#include "model.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

enum class SceneObjectEvents : unsigned int { MODEL_MATRIX_CHANGED,
                                              DATA_UPDATE };

class SceneObject : public Subject<SceneObjectEvents> {
    friend class Model;

    public:
        SceneObject()=delete;
        SceneObject(SceneObject * parent, std::string name, int priority);
        SceneObject(const SceneObject &)=delete;
        SceneObject & operator=(const SceneObject &)=delete;
        ~SceneObject();

        std::string Name() const;
        int Key() const;
        int Priority() const;

        const glm::mat4 & ModelMatrixRef() const;
        const glm::mat4 & CombineModelMatrixRef() const;  // Combined a segment model matrix and parent the segment model matrix
        void SetModelMatrix(const glm::mat4 & model_matrix);
        void Translate(const glm::vec3 & vector);
        void Scale(const glm::vec3 & scale_coef);
        void Rotate(const glm::vec3 & axis, float angle_in_deg);

        void SetObjectOption(unsigned int option);
        void ResetObjectOption(unsigned int option);
        bool TestObjectOption(unsigned int option);
        unsigned int GetObjectOptions();

    private:
        void SetKey(int key);
        void CalculateModelMatrix();
        void ParentModelMatrixChanged(const EventInfo & info);

        SceneObject * parent;
        int key;
        std::string name;     
        int priority;   
        unsigned int object_options;

        glm::mat4 model_matrix;
        glm::mat4 parent_model_matrix;
        glm::mat4 combine_model_matrix;

        std::vector<std::unique_ptr<SceneObject>> scene_objects;

        std::vector<unsigned int> observer_ids;
};

#endif
