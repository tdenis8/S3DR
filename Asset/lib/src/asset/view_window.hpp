#ifndef _VIEW_WINDOW_HPP_
#define _VIEW_WINDOW_HPP_

#include "model/model_handler.hpp"

#include <string>

class FPSCounter
{
    public:
    FPSCounter(TextObject& text_object, unsigned int text_id);
    void print();

    private:
    TextObject& text_object;
    unsigned int text_id;
    double last_time;
    int num_frames;
};

void
ViewWindow(Model& model, const std::string& title, bool show_fps_counter, const std::string& fps_counter_font_path);

void ViewWindow(Model& model,
                const std::string& title,
                std::function<void(void)> cb_function,
                bool show_fps_counter,
                const std::string& fps_counter_font_path);

#endif