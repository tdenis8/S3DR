#include "select_operator.hpp"

#include "model/model.hpp"
/*#include "model/shell_object.hpp"*/

#include "view/view.hpp"
#include "view/selection_set.hpp"

SelectOperator::SelectOperator(View &view)
    : Operator(view), options(0), captured_x(0), captured_y(0), scene_object_key(0)
{
}

SelectOperator::~SelectOperator()
{
}

int SelectOperator::OnLeftButtonDown(const MouseEventInfo &info)
{
    captured_x = info.X();
    captured_y = info.Y();
    return 1;
}

int SelectOperator::OnLeftButtonUp(const MouseEventInfo &info)
{
    if(captured_x != info.X() || captured_y != info.Y())
    {
        scene_object_key = 0;
        return 0;
    }

    // If ctrl key is not presed
    if(!pressed_keys.count(289))
    {
        // Unselect previously selected elements
    }

    auto &selection_set = view.GetSelectionSet();
    selection_set.CalculateSelection(info.X(), info.Y());
    auto selection_data = selection_set.GetSelectionData();
    scene_object_key = selection_data.scene_object_key;

    return 1;
}

int SelectOperator::OnNoButtonDownAndMove(const MouseEventInfo &info)
{
    if(!GetOption(SelectOperatorOption::MOUSE_TRACKING))
    {
        scene_object_key = 0;
        return 0;
    }

    auto &selection_set = view.GetSelectionSet();
    selection_set.CalculateSelection(info.X(), info.Y());
    auto selection_data = selection_set.GetSelectionData();
    scene_object_key = selection_data.scene_object_key;

    if(GetOption(SelectOperatorOption::TARGET_HIGHLIGHT))
    {
        /*        // If previously highlighted object is current active object
                if(highlighted_scene_object_key == scene_object_key)
                {
                    return 1;
                }
                // Unhighlight previously highlighted object
                if(highlighted_scene_object_key)
                {
                    Model *model_ptr = view.ModelPtr();
                    SceneObject *scene_object_ptr = model_ptr->GetSceneObject(highlighted_scene_object_key);
                    if(ShellObject *shell_object_ptr = dynamic_cast<ShellObject *>(scene_object_ptr))
                    {
                        shell_object_ptr->Highlight(false);
                        highlighted_scene_object_key = 0;
                    }
                }
                // Highlight new object
                if(scene_object_key)
                {
                    Model *model_ptr = view.ModelPtr();
                    SceneObject *scene_object_ptr = model_ptr->GetSceneObject(scene_object_key);
                    if(ShellObject *shell_object_ptr = dynamic_cast<ShellObject *>(scene_object_ptr))
                    {
                        shell_object_ptr->Highlight(true);
                        highlighted_scene_object_key = scene_object_key;
                    }
                }*/
    }

    return 1;
}

int SelectOperator::OnKeyDown(const KeyboardEventInfo &info)
{
    pressed_keys.insert(info.Key());
}

int SelectOperator::OnKeyUp(const KeyboardEventInfo &info)
{
    pressed_keys.erase(info.Key());
}

void SelectOperator::SetOption(SelectOperatorOption option)
{
    options |= static_cast<unsigned int>(option);
}

void SelectOperator::ResetOption(SelectOperatorOption option)
{
    options &= ~static_cast<unsigned int>(option);
}

bool SelectOperator::GetOption(SelectOperatorOption option)
{
    return options & static_cast<unsigned int>(option);
}

unsigned int SelectOperator::SceneObjectKey()
{
    return scene_object_key;
}