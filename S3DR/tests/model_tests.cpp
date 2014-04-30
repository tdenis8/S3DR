#include "model_tests.hpp"

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

bool TestTextureShell(){
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

    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}

bool TestLine(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GenerateLineObject(nullptr, "Line");
    LineObject & line_object = model_handler->GetLineObject(id);

    std::vector<glm::vec3> points{glm::vec3(0,0,0), 
                                  glm::vec3(1.0,0.0,0),
                                  glm::vec3(1,1,0),
                                  glm::vec3(0.5,1.5,0),
                                  glm::vec3(0.0,1.0,0)};
    points.push_back(MeanPoint(points));

    std::vector<glm::vec4> colors(points.size(), glm::vec4(1.0, 1.0, 0.0, 1.0));

    std::vector<glm::ivec2> indices {glm::ivec2(0, 1), 
                                     glm::ivec2(1, 2),
                                     glm::ivec2(2, 3),
                                     glm::ivec2(3, 4),
                                     glm::ivec2(4, 0)};   

    line_object.AppendData(points, colors, indices);

    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}

bool TestPoint(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GeneratePointObject(nullptr, "Point");
    PointObject & point_object = model_handler->GetPointObject(id);

    std::vector<glm::vec3>  points;
    std::vector<glm::ivec3>  _trash;
    GenerateSphere(glm::vec3(5,5,5), 2.4, points, _trash);

    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

    std::vector<int> indices;
    for(int i; i<points.size(); ++i){
        indices.push_back(i);
    }

    point_object.AppendData(points, colors, indices);

    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}


void RunModelTests(){
    std::cout<<"Model tests: "<<std::endl;
    auto all = true;
    if(all){
        TestShell_1();
        TestShell_2();
        TestTextureShell();
        TestLine();
        TestPoint();
    }
    else{
        
    }
    std::cout<<std::endl;
}