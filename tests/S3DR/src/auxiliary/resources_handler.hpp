#ifndef _RESOURCES_HANDLER_HPP_
#define _RESOURCES_HANDLER_HPP_

#include <string>

void set_main_resource_path(const std::string& path);

std::string get_main_resource_path();
std::string get_fonts_resources_path();
std::string get_models_resources_path();
std::string get_textures_resources_path();

#endif