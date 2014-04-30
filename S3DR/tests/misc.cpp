#include "misc.hpp"

#include "utility/custom_exp.hpp"
#include "asset/view_window.hpp"

#include <iostream>

bool RunWithinTestEnv(Model * model, const std::string & test_name){
    try{
        ViewWindow(model, test_name);
    }
    catch(CustomExp e){
        std::cerr<<"*** Test "<<test_name<<" -> Failed "<<std::endl;
        std::cerr<<e.what()<<std::endl<<std::endl;
        return false;
    }
    std::cout<<"*** Test "<<test_name<<" -> Visual test "<<std::endl;
    return true;
}