#ifndef _VIEW_WINDOW_HPP_
#define _VIEW_WINDOW_HPP_

#include "model/model.hpp"

#include <string>

void ViewWindow(Model * model, const std::string & title);
void ViewWindow(Model * model, const std::string & title, std::function<void(void)> cb_function);

#endif