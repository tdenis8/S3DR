#include "shell_tests.hpp"

#include "utility/math_utils.hpp"
#include "asset/3D_shapes.hpp"
#include "asset/assimp_mesh_loader.hpp"
#include "model/model_manager.hpp"

#include "auxiliary/test_env.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestMaterialShell1()
{
    // Create new model
    std::unique_ptr<ModelManager> model_manager(new ModelManager("Model1"));

    // Add shell object to the model
    int id = model_manager->GenerateMaterialShellObject(nullptr, "Shell1");
    MaterialShellObject& material_shell_object = model_manager->GetMaterialShellObject(id);

    // Data for rendering
    std::vector<glm::vec3> points{
        glm::vec3(0, 0, 0), glm::vec3(1.0, 0.0, 0), glm::vec3(1, 1, 0), glm::vec3(0.5, 1.5, 0), glm::vec3(0.0, 1.0, 0)};
    points.push_back(MeanPoint(points));
    std::vector<glm::ivec3> indices{
        glm::ivec3(0, 1, 5), glm::ivec3(1, 2, 5), glm::ivec3(2, 3, 5), glm::ivec3(3, 4, 5), glm::ivec3(4, 0, 5)};

    // Load data to previous created object
    material_shell_object.AppendData(points, indices, Material());

    // Create view and attach model to it
    return RunWithinTestEnv(model_manager->GetModel(), std::string(__FUNCTION__));
}

bool TestMaterialShell2()
{
    // Create new model
    std::unique_ptr<ModelManager> model_manager(new ModelManager("Model1"));

    // Add shell object to the model
    int id1 = model_manager->GenerateMaterialShellObject(nullptr, "Shell1");
    MaterialShellObject& material_shell_object1 = model_manager->GetMaterialShellObject(id1);

    {
        // Generate a sphere
        std::vector<glm::vec3> points;
        std::vector<glm::ivec3> indices;
        GenerateSphere(glm::vec3(-4, -3.5, -3.8), 2.4, points, indices);

        // Default material
        Material material;

        // Load data to previous created object
        material_shell_object1.AppendData(points, indices, material);
    }

    {
        // Generate a sphere
        std::vector<glm::vec3> points;
        std::vector<glm::ivec3> indices;
        GenerateSphere(glm::vec3(0, 0, 0), 1.5, points, indices);

        // Custom material
        Material material;

        material.diffuse = glm::vec3(1.0, 1.0, 0.0);
        material.specular = glm::vec3(1.0, 1.0, 0.0);

        // Load data to previous created object
        material_shell_object1.AppendData(points, indices, material);
    }

    {
        // Add shell object to the model
        int id2 = model_manager->GenerateMaterialShellObject(nullptr, "Shell2");
        MaterialShellObject& material_shell_object2 = model_manager->GetMaterialShellObject(id2);

        // Custom material
        Material material;

        material.diffuse = glm::vec3(1.0, 0.0, 0.0);
        material.specular = glm::vec3(1.0, 0.0, 0.0);

        // Load data to previous created object
        LoadAssimpMesh(get_models_resources_path() + "/Suzy/Suzy.obj", material_shell_object2, material);

        material_shell_object2.Translate(glm::vec3(3, 3, 3));
    }

    // Create view and attach model to it
    return RunWithinTestEnv(model_manager->GetModel(), std::string(__FUNCTION__));
}

void RunShellTests()
{
    std::cout << "Shell tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if(all)
    {
        TestMaterialShell1();
        std::cout << std::endl;
        TestMaterialShell2();
    }
    else
    {
    }
    std::cout << std::endl;
}