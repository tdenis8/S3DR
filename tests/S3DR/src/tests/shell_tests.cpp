#include "shell_tests.hpp"

#include "utility/math_utils.hpp"
#include "asset/3D_shapes.hpp"
#include "asset/assimp_mesh_loader.hpp"
#include "model/model_handler.hpp"

#include "auxiliary/test_env.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestShell_1()
{
    // Create new model
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1"));

    // Add shell object to the model
    int id = model_handler->GenerateShellObject(nullptr, "Shell1");
    ShellObject& shell_object = model_handler->GetShellObject(id);

    // Data for rendering
    std::vector<glm::vec3> points{
        glm::vec3(0, 0, 0), glm::vec3(1.0, 0.0, 0), glm::vec3(1, 1, 0), glm::vec3(0.5, 1.5, 0), glm::vec3(0.0, 1.0, 0)};
    points.push_back(MeanPoint(points));
    std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));
    std::vector<glm::ivec3> indices{
        glm::ivec3(0, 1, 5), glm::ivec3(1, 2, 5), glm::ivec3(2, 3, 5), glm::ivec3(3, 4, 5), glm::ivec3(4, 0, 5)};

    // Load data to previous created object
    shell_object.AppendData(points, colors, indices);

    // Create view and attach model to it
    return RunWithinTestEnv(model_handler->GetModel(), std::string(__FUNCTION__));
}

bool TestShell_2()
{
    // Create new model
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1"));

    // Add shell object to the model
    int id = model_handler->GenerateShellObject(nullptr, "Shell2");
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
        GenerateSphere(glm::vec3(5, 5, 0), 1.5, points, indices);
        std::vector<glm::vec4> colors(points.size(), glm::vec4(1.0, 0.0, 0.0, 1.0));

        // Load data to previous created object
        shell_object.AppendData(points, colors, indices);
    }

    // Create view and attach model to it
    return RunWithinTestEnv(model_handler->GetModel(), std::string(__FUNCTION__), true);
}

bool TestTextureShell_1()
{
    // Create new model
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1"));

    // Add texture shell object to the model
    unsigned int id = model_handler->GenerateTextureShellObject(nullptr, "TextureShell1");
    TextureShellObject& texture_shell_object1 = model_handler->GetTextureShellObject(id);

    // Load data to previous created object
    LoadAssimpMesh(get_models_resources_path() + "/Earth/Earth.obj", texture_shell_object1);

    // Move and scale object
    texture_shell_object1.Translate(glm::vec3(-1, -1, 0));
    texture_shell_object1.Scale(glm::vec3(2, 2, 2));

    // Create view and attach model to it
    return RunWithinTestEnv(model_handler->GetModel(), std::string(__FUNCTION__));
}

void RunShellTests()
{
    std::cout << "Shell tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if(all)
    {
        TestShell_1();
        std::cout << std::endl;
        TestShell_2();
        std::cout << std::endl;
        TestTextureShell_1();
    }
    else
    {
    }
    std::cout << std::endl;
}