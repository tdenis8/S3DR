#include "point_tests.hpp"

#include "model/model_manager.hpp"
#include "asset/3D_shapes.hpp"

#include "auxiliary/test_env.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestPoint1()
{
    // Create new model
    std::unique_ptr<ModelManager> model_manager(new ModelManager("Model1"));

    // Add point object to the model
    int id = model_manager->GeneratePointObject(nullptr, "Point");
    PointObject& point_object = model_manager->GetPointObject(id);

    // Points data
    std::vector<glm::vec3> points;
    std::vector<glm::ivec3> _trash;
    GenerateSphere(glm::vec3(2, 2, 2), 2.4, points, _trash);

    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

    std::vector<int> indices;
    for(int i = 0; i < points.size(); ++i)
    {
        indices.push_back(i);
    }

    // Load data to previous created object
    point_object.AppendData(points, colors, indices);

    // Create view and attach model to it
    return RunWithinTestEnv(model_manager->GetModel(), std::string(__FUNCTION__));
}

void RunPointTests()
{
    std::cout << "Point tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if(all)
    {
        TestPoint1();
    }
    else
    {
    }
    std::cout << std::endl;
}