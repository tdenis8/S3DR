#ifndef _VIEW_ADAPTER_H_
#define _VIEW_ADAPTER_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

// Forward declarations
class View;
class Camera;
struct ViewSettings;

/// \brief ...
///
/// Render data in model
class ViewAdapter
{
    public:
    ViewAdapter() = delete;
    ViewAdapter(View &view);
    ViewAdapter(const ViewAdapter &) = delete;
    ViewAdapter &operator=(const ViewAdapter &) = delete;
    virtual ~ViewAdapter();

    virtual void Render() = 0;
    virtual float ScreenDepthAt(int x, int y) const = 0;

    protected:
    View &view_;
    Camera &camera_;
    ViewSettings &view_settings_;
};

#endif