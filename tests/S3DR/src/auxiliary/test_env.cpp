#include "test_env.hpp"

#include "utility/custom_exp.hpp"

#include <iostream>

bool RunWithinTestEnv(Model& model, const std::string& test_name, bool show_fps_counter)
{
    try
    {
        std::string font_path = get_fonts_resources_path();
        font_path += font_path.size() > 0 ? "DejaVuSansMono-Bold.ttf" : "";
        ViewWindow(model, test_name, show_fps_counter, font_path);
    }
    catch(CustomExp e)
    {
        std::cerr << "*** Test " << test_name << " -> Failed " << std::endl;
        std::cerr << e.what() << std::endl << std::endl;
        return false;
    }
    std::cout << "*** Test " << test_name << " -> Visual test " << std::endl;
    return true;
}

bool RunWithinTestEnv(Model& model,
                      const std::string& test_name,
                      std::function<void(void)> cb_function,
                      bool show_fps_counter)
{
    try
    {
        std::string font_path = get_fonts_resources_path();
        font_path += font_path.size() > 0 ? "DejaVuSansMono-Bold.ttf" : "";
        ViewWindow(model, test_name, cb_function, show_fps_counter, font_path);
    }
    catch(CustomExp e)
    {
        std::cerr << "*** Test " << test_name << " -> Failed " << std::endl;
        std::cerr << e.what() << std::endl << std::endl;
        return false;
    }
    std::cout << "*** Test " << test_name << " -> Visual test " << std::endl;
    return true;
}