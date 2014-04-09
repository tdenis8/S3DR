#include "auxiliary_tests.hpp"

#include "utility/custom_exp.hpp"
#include "utility/math_utils.hpp"

#include "model/model.hpp"
#include "model/shell_object.hpp"
#include "model/line_object.hpp"
#include "model/point_object.hpp"

#include "misc/view_window.hpp"
#include "misc/3D_shapes.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <iostream>
#include <vector>

bool TestShellObject(){
    std::unique_ptr<Model> model{new Model("Model1")}; 
    
    std::shared_ptr<ShellObject> shell1(new ShellObject(nullptr, "Shell1", 2)); 
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
    shell1->AppendData(points, colors, indices);
    model->InsertSceneObject(shell1);

    std::shared_ptr<ShellObject> shell3(new ShellObject(nullptr, "Sphere")); 
    // shell3->SetObjectOption(static_cast<unsigned int>(ShellOption::Transparency));
    GenerateSphereData(glm::vec3(5,5,5),2.4, shell3);
    model->InsertSceneObject(shell3);
    

    try{
        std::cout<<"<---"<<std::endl;
        ViewWindow(model.get(), "Test ShellObject");
        std::cout<<"--->"<<std::endl;
    }
    catch(CustomExp e){
        std::cerr<<"*** Test "<<std::string(__FUNCTION__)<<" -> Failed "<<std::endl;
        std::cerr<<e.what()<<std::endl<<std::endl;
        return false;
    }
    std::cout<<"*** Test "<<std::string(__FUNCTION__)<<" -> Visual test "<<std::endl;
    return true;
}

bool TestLineObject(){
    std::unique_ptr<Model> model{new Model("Model1")}; 
        
    std::shared_ptr<LineObject> line1(new LineObject(nullptr, "Line1")); 
    std::vector<glm::vec3> points{glm::vec3(0,0,0), 
                                  glm::vec3(1.0,0.0,0),
                                  glm::vec3(1,1,0),
                                  glm::vec3(0.5,1.5,0),
                                  glm::vec3(0.0,1.0,0)};
    points.push_back(MeanPoint(points));

    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

    std::vector<glm::ivec2> indices {glm::ivec2(0, 1), 
                                     glm::ivec2(1, 2),
                                     glm::ivec2(2, 3),
                                     glm::ivec2(3, 4),
                                     glm::ivec2(4, 0)};      
    line1->AppendData(points, colors, indices);

    model->InsertSceneObject(line1);

    try{
        std::cout<<"<---"<<std::endl;
        ViewWindow(model.get(), "Test LineObject");
        std::cout<<"--->"<<std::endl;
    }
    catch(CustomExp e){
        std::cerr<<"*** Test "<<std::string(__FUNCTION__)<<" -> Failed "<<std::endl;
        std::cerr<<e.what()<<std::endl<<std::endl;
        return false;
    }
    std::cout<<"*** Test "<<std::string(__FUNCTION__)<<" -> Visual test "<<std::endl;
    return true;
}

bool TestPointObject(){
    std::unique_ptr<Model> model{new Model("Model1")}; 
        
    std::shared_ptr<PointObject> point1(new PointObject(nullptr, "Point1")); 
    std::vector<glm::vec3> points{glm::vec3(0,0,0), 
                                  glm::vec3(1.0,0.0,0),
                                  glm::vec3(1,1,0),
                                  glm::vec3(0.5,1.5,0),
                                  glm::vec3(0.0,1.0,0)};
    points.push_back(MeanPoint(points));
    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.5, 0.0, 0.2, 1.0));
    std::vector<int> indices {0,1,2,3,4,5}; 

    point1->AppendData(points, colors, indices);
    model->InsertSceneObject(point1);

    try{
        std::cout<<"<---"<<std::endl;
        ViewWindow(model.get(), "Test PointObject");
        std::cout<<"--->"<<std::endl;
    }
    catch(CustomExp e){
        std::cerr<<"*** Test "<<std::string(__FUNCTION__)<<" -> Failed "<<std::endl;
        std::cerr<<e.what()<<std::endl<<std::endl;
        return false;
    }
    std::cout<<"*** Test "<<std::string(__FUNCTION__)<<" -> Visual test "<<std::endl;
    return true;
}

void RunAuxiliaryTests(){
    std::cout<<"Auxiliary tests: "<<std::endl;
    auto all = true;
    if(all){
        TestShellObject();
        TestLineObject();
        TestPointObject();
    }
    else{
        
    }
    std::cout<<std::endl;
}
