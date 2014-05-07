#include "shell_tests.hpp"

#include "utility/math_utils.hpp"
#include "asset/3D_shapes.hpp"
#include "asset/assimp_mesh_loader.hpp"
#include "model/model_handler.hpp"

#include "misc.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestShell_1(){
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

    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}

bool TestShell_2(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GenerateShellObject(nullptr, "Shell2");
    ShellObject & shell_object = model_handler->GetShellObject(id);

    {
        std::vector<glm::vec3>  points;
        std::vector<glm::ivec3>  indices;
        GenerateSphere(glm::vec3(0,0,0), 2.4, points, indices);
        std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

        shell_object.AppendData(points, colors, indices);
    }


    {
        std::vector<glm::vec3>  points;
        std::vector<glm::ivec3>  indices;
        GenerateSphere(glm::vec3(5,5,0), 1.5, points, indices);
        std::vector<glm::vec4> colors(points.size(), glm::vec4(1.0, 0.0, 0.0, 1.0));

        shell_object.AppendData(points, colors, indices);
    }

    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}

bool TestTextureShell_1(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GenerateTextureShellObject(nullptr, "TextureShell1");
    TextureShellObject & texture_shell_object1 = model_handler->GetTextureShellObject(id);
    LoadAssimpMesh("../resources/Crate/Crate1.obj", texture_shell_object1);
    texture_shell_object1.Scale(glm::vec3(2,2,2));
    texture_shell_object1.Translate(glm::vec3(1,1,0));

    id = model_handler->GenerateTextureShellObject(nullptr, "TextureShell2");
    TextureShellObject & texture_shell_object2 = model_handler->GetTextureShellObject(id);
    LoadAssimpMesh("../resources/Earth/Earth.obj", texture_shell_object2);
    texture_shell_object2.Translate(glm::vec3(-1,-1,0));
    texture_shell_object2.Scale(glm::vec3(2,2,2));
    
    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}


void RunShellTests(){
    std::cout<<"Shell tests: "<<std::endl;
    std::cout<<"--------------------------"<<std::endl;
    auto all = true;
    if(all){
        TestShell_1();
        TestShell_2();
        TestTextureShell_1();
    }
    else{
        
    }
    std::cout<<std::endl;
}