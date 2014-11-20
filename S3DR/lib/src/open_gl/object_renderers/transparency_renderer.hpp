#ifndef _TRANSPARENCY_RENDERER_H_
#define _TRANSPARENCY_RENDERER_H_

#include "misc/dual_depth_peeling.hpp"

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>
#include <string>

class ShellAdapter;
class DualDepthPeeling;

enum class DDPPassType
{
    INIT,
    PEEL,
    BLEND,
    FINAL
};

class TransparencyRenderer : public SceneObjectRenderer
{
    friend DualDepthPeeling;

    public:
    TransparencyRenderer();
    TransparencyRenderer(const TransparencyRenderer &) = delete;
    TransparencyRenderer &operator=(const TransparencyRenderer &) = delete;
    ~TransparencyRenderer();

    void ActivateProgram(DDPPassType type);
    void DeactivateProgram();

    void AttachShellAdapter(ShellAdapter *shell_adapter);
    void Reset();

    void SetWidthHeight(int width, int height);
    void SetBackgroundColor(const glm::vec4 &background_color);

    void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

    private:
    static std::vector<Shader> GetEmptyShaderList();
    static std::vector<Shader> GetInitProgramShaderList();
    static std::vector<Shader> GetPillProgramShaderList();
    static std::vector<Shader> GetBlendProgramShaderList();
    static std::vector<Shader> GetFinalProgramShaderList();

    void SetModelToClipMatrixPA(const glm::mat4 &model_to_clip_matrix);
    void SetModelToCameraMatrixPA(const glm::mat4 &model_to_camera_matrix);
    void SetNormalModelToCameraMatrixPA(const glm::mat3 &normal_model_to_camera_matrix);

    void BindTexture(GLenum target, std::string texname, GLuint texid, int texunit);
    void SetAlphaPA(float alpha);

    Program init_program_;
    Program peel_program_;
    Program blend_program_;
    Program final_program_;

    DualDepthPeeling dual_depth_peeling_;

    std::vector<ShellAdapter *> shell_adapters_[3];
};

#endif