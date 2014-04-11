#ifndef _TRANSPARENCY_RENDERER_H_
#define _TRANSPARENCY_RENDERER_H_

#include "scene_object_renderer.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <string>

class ShellAdapter;
class DualDepthPeeling;

enum class DDPPassType {INIT, PEEL, BLEND, FINAL};

class TransparencyRenderer : public SceneObjectRenderer {
    friend DualDepthPeeling;

    public:
        TransparencyRenderer();
        ~TransparencyRenderer();
        TransparencyRenderer(const TransparencyRenderer &)=delete;
        TransparencyRenderer & operator=(const TransparencyRenderer &)=delete;

        void ActivateProgram(DDPPassType type);
        void DeactivateProgram();

        void AttachShellAdapter(ShellAdapter * shell_adapter);
        void Reset();
        
        void SetWidthHeight(int width, int height);
        void SetBackgroundColor(const glm::vec4 & background_color);

        void Render(const glm::mat4 & view, const glm::mat4 & projection,  int priority);
        
    private:
        void InitPrograms();
        void SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix);
        void SetModelToCameraMatrixPA(const glm::mat4 & model_to_camera_matrix);
        void SetNormalModelToCameraMatrixPA(const glm::mat3 & normal_model_to_camera_matrix);
        
        void BindTexture(GLenum target, std::string texname, GLuint texid, int texunit);
        void SetAlphaPA(float alpha);

        std::shared_ptr<Program> init_program;
        std::shared_ptr<Program> peel_program;
        std::shared_ptr<Program> blend_program;
        std::shared_ptr<Program> final_program;

        std::shared_ptr<DualDepthPeeling> dual_depth_peeling;

        std::vector<ShellAdapter *> shell_adapters[3];
};

#endif