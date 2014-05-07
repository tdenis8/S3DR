#ifndef _MISC_H_
#define _MISC_H_

#include "model/model.hpp"

#include <string>

bool RunWithinTestEnv(Model* model, const std::string& test_name);
bool RunWithinTestEnv(Model* model, const std::string& test_name, std::function<void(void)> cb_function);

#endif