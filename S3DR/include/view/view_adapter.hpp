#ifndef _VIEW_ADAPTER_H_
#define _VIEW_ADAPTER_H_

#include <glm/glm.hpp>

// Forward declarations
class View;
struct ViewSettings;

/// \brief ...
///
/// Render data in model
class ViewAdapter {
    public:
    	ViewAdapter()=delete;
        ViewAdapter(View & view);
        ViewAdapter(const ViewAdapter &)=delete;
        ViewAdapter & operator=(const ViewAdapter &)=delete;
        virtual ~ViewAdapter();

        virtual void Render(const glm::mat4 & view_matrix, const glm::mat4 & projection_matrix) = 0;
        virtual float ScreenDepthAt(int x, int y) const = 0;
    
    protected:
        const ViewSettings & ViewSettingsRef() const;
        
        View & view;   	
};

#endif