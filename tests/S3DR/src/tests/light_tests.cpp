#include "light_tests.hpp"

#include "utility/math_utils.hpp"
#include "asset/3D_shapes.hpp"
#include "model/model_manager.hpp"

#include "auxiliary/test_env.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestLight_1()
{
    // Create new model
    std::unique_ptr<ModelManager> model_manager(new ModelManager("Model1"));

    // Add light object to the model

    // Add shell object to the model
    /*    int id = model_handler->GenerateShellObject(nullptr, "Shell1");
        ShellObject& shell_object = model_handler->GetShellObject(id);

        {
            // Generate a sphere
            std::vector<glm::vec3> points;
            std::vector<glm::ivec3> indices;
            GenerateSphere(glm::vec3(0, 0, 0), 2.4, points, indices);
            std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

            // Load data to previous created object
            shell_object.AppendData(points, colors, indices);
        }

        {
            // Generate a sphere
            std::vector<glm::vec3> points;
            std::vector<glm::ivec3> indices;
            GenerateSphere(glm::vec3(5, 5, 0), 2.5, points, indices);
            std::vector<glm::vec4> colors(points.size(), glm::vec4(0.0, 0.0, 1.0, 1.0));

            // Load data to previous created object
            shell_object.AppendData(points, colors, indices);
        }*/

    // Create view and attach model to it
    return RunWithinTestEnv(model_manager->GetModel(), std::string(__FUNCTION__), true);
}

void RunLightTests()
{
    std::cout << "Light tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if(all)
    {
        TestLight_1();
        std::cout << std::endl;
        /*        TestLight_1();
                std::cout << std::endl;*/
    }
    else
    {
    }
    std::cout << std::endl;
}