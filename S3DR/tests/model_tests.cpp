#include "model_tests.hpp"

#include "utility/custom_exp.hpp"
#include "utility/math_utils.hpp"

#include "asset/view_window.hpp"
#include "asset/3D_shapes.hpp"

#include "model/model_handler.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool InsertShell_1(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GenerateShellObject(nullptr, "Shell1");
    ShellObject & shell_object = model_handler->GetShellObject(id);

    std::vector<glm::vec3> points{glm::vec3(0,0,0), 
                                  glm::vec3(1.0,0.0,0),
                                  glm::vec3(1,1,0),
                                  glm::vec3(0.5,1.5,0),
                                  glm::vec3(0.0,1.0,0)};
    points.push_back(MeanPoint(points));

    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

    std::vector<glm::ivec3> indices {glm::ivec3(0, 1, 5), 
                                     glm::ivec3(1, 2, 5),
                                     glm::ivec3(2, 3, 5),
                                     glm::ivec3(3, 4, 5),
                                     glm::ivec3(4, 0, 5)};  

    shell_object.AppendData(points, colors, indices);

    try{
        ViewWindow(&model_handler->GetModel(), std::string(__FUNCTION__));
    }
    catch(CustomExp e){
        std::cerr<<"*** Test "<<std::string(__FUNCTION__)<<" -> Failed "<<std::endl;
        std::cerr<<e.what()<<std::endl<<std::endl;
        return false;
    }
    std::cout<<"*** Test "<<std::string(__FUNCTION__)<<" -> Visual test "<<std::endl;
    return true;
}

bool InsertShell_2(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GenerateShellObject(nullptr, "Shell2");
    ShellObject & shell_object = model_handler->GetShellObject(id);

    GenerateSphere(shell_object, glm::vec3(5,5,5), 2.4);

    try{
        ViewWindow(&model_handler->GetModel(), std::string(__FUNCTION__));
    }
    catch(CustomExp e){
        std::cerr<<"*** Test "<<std::string(__FUNCTION__)<<" -> Failed "<<std::endl;
        std::cerr<<e.what()<<std::endl<<std::endl;
        return false;
    }
    std::cout<<"*** Test "<<std::string(__FUNCTION__)<<" -> Visual test "<<std::endl;
    return true;
}

void RunModelTests(){
    std::cout<<"Model tests: "<<std::endl;
    auto all = true;
    if(all){
        InsertShell_1();
        InsertShell_2();
    }
    else{
        
    }
    std::cout<<std::endl;
}