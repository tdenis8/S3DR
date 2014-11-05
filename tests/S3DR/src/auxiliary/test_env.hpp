#ifndef _TEST_ENV_H_
#define _TEST_ENV_H_

#include "model/model.hpp"
#include "asset/view_window.hpp"

#include "resources_handler.hpp"

#include <string>

bool RunWithinTestEnv(Model& model, const std::string& test_name, bool show_fps_counter = false);
bool RunWithinTestEnv(Model& model,
                      const std::string& test_name,
                      std::function<void(void)> cb_function,
                      bool show_fps_counter = false);

#endif