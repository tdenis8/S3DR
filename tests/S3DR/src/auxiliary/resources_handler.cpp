#include "resources_handler.hpp"

static std::string __main_resource_path__;

void set_main_resource_path(const std::string& path)
{
    __main_resource_path__ = path;
}

std::string get_main_resource_path()
{
    return __main_resource_path__;
}

std::string get_fonts_resources_path()
{
    return get_main_resource_path() + "/fonts/";
}

std::string get_models_resources_path()
{
    return get_main_resource_path() + "/models/";
}

std::string get_textures_resources_path()
{
    return get_main_resource_path() + "/textures/";
}