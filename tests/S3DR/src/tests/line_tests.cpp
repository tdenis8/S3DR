#include "line_tests.hpp"

#include "utility/math_utils.hpp"
#include "model/model_handler.hpp"

#include "auxiliary/test_env.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestLine1()
{
    // Create new model
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1"));

    // Add line object to the model
    int id = model_handler->GenerateLineObject(nullptr, "Line");
    LineObject& line_object = model_handler->GetLineObject(id);

    // Line data
    std::vector<glm::vec3> points{
        glm::vec3(0, 0, 0), glm::vec3(1.0, 0.0, 0), glm::vec3(1, 1, 0), glm::vec3(0.5, 1.5, 0), glm::vec3(0.0, 1.0, 0)};
    points.push_back(MeanPoint(points));

    std::vector<glm::vec4> colors(points.size(), glm::vec4(1.0, 1.0, 0.0, 1.0));

    std::vector<glm::ivec2> indices{
        glm::ivec2(0, 1), glm::ivec2(1, 2), glm::ivec2(2, 3), glm::ivec2(3, 4), glm::ivec2(4, 0)};

    // Load data to previous created object
    line_object.AppendData(points, colors, indices);

    // Create view and attach model to it
    return RunWithinTestEnv(model_handler->GetModel(), std::string(__FUNCTION__));
}

void RunLineTests()
{
    std::cout << "Line tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if(all)
    {
        TestLine1();
    }
    else
    {
    }
    std::cout << std::endl;
}