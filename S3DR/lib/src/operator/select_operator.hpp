#ifndef _SELECT_OPERATOR_H_
#define _SELECT_OPERATOR_H_

#include "operator.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>
#include <set>

enum class SelectOperatorOption : unsigned int
{
    MOUSE_TRACKING = 1,
    TARGET_HIGHLIGHT = 2
};

class SelectOperator : public Operator
{
public:
    SelectOperator(View& view);
    virtual ~SelectOperator();

    int OnLeftButtonDown(const MouseEventInfo& info);
    int OnLeftButtonUp(const MouseEventInfo& info);

    int OnNoButtonDownAndMove(const MouseEventInfo& info);

    int OnKeyDown(const KeyboardEventInfo& info);
    int OnKeyUp(const KeyboardEventInfo& info);

    void SetOption(SelectOperatorOption option);
    void ResetOption(SelectOperatorOption option);
    bool GetOption(SelectOperatorOption option);

    unsigned int SceneObjectKey();

private:
    unsigned int options;
    int captured_x;
    int captured_y;
    std::set<int> pressed_keys;

    unsigned int scene_object_key;
    unsigned int highlighted_scene_object_key;
};

#endif