#ifndef _SCENE_SETTINGS_H_
#define _SCENE_SETTINGS_H_

#include "utility/subject.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

enum class SceneSettingsEvents : unsigned int
{
   WIDTH_HEIGHT_CHANGED,
   BACKGROUND_COLOR_CHANGED
};

class SceneSettings : public Subject<SceneSettingsEvents>
{
   public:
   SceneSettings();
   SceneSettings(const SceneSettings &) = delete;
   SceneSettings &operator=(const SceneSettings &) = delete;
   ~SceneSettings();

   void SetWidthHeight(int width, int height);
   int Width();
   int Height();

   void SetBackgroundColor(const glm::vec3 &color);
   const glm::vec3 &BackgroundColor();

   private:
   int width;
   int height;

   glm::vec3 background_color;
};

#endif