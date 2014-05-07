#include "point_tests.hpp"

#include "model/model_handler.hpp"
#include "asset/3D_shapes.hpp"

#include "misc.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestPoint1(){
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1")); 

    int id = model_handler->GeneratePointObject(nullptr, "Point");
    PointObject & point_object = model_handler->GetPointObject(id);

    std::vector<glm::vec3>  points;
    std::vector<glm::ivec3>  _trash;
    GenerateSphere(glm::vec3(2,2,2), 2.4, points, _trash);

    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

    std::vector<int> indices;
    for(int i; i<points.size(); ++i){
        indices.push_back(i);
    }

    point_object.AppendData(points, colors, indices);

    return RunWithinTestEnv(&model_handler->GetModel(), std::string(__FUNCTION__));
}


void RunPointTests(){
    std::cout<<"Point tests: "<<std::endl;
    std::cout<<"--------------------------"<<std::endl;
    auto all = true;
    if(all){
        TestPoint1();
    }
    else{
        
    }
    std::cout<<std::endl;
}