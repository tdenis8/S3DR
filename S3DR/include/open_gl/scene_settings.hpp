#ifndef _SCENE_SETTINGS_H_
#define _SCENE_SETTINGS_H_

#include "misc/subject.hpp"
#include "misc/lights.hpp"

#include <glm/glm.hpp>

enum class SceneSettingsEvents : unsigned int { WIDTH_HEIGHT_CHANGED,
                                                BACKGROUND_COLOR_CHANGED,
                                                LIGHTS_CHANGED };


class SceneSettings : public Subject<SceneSettingsEvents> {
    public:
        SceneSettings();
        SceneSettings(const SceneSettings &)=delete;
        SceneSettings & operator=(const SceneSettings &)=delete;
        ~SceneSettings();
        
        void SetWidthHeight(int width, int height);
        int Width();
        int Height();

        void SetBackgroundColor(const glm::vec3 & color);
        const glm::vec3 & BackgroundColor();

        
        bool PushLightToScene(const Light & light);
        const LightsBlock & LightsBlockInCameraSpace(const glm::mat4 & view_matrix);

    private:
        int width;
        int height;

        glm::vec3 background_color;
        Lights lights;   
};
    
#endif