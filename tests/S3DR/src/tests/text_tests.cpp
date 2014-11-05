#include "text_tests.hpp"

#include "asset/3D_shapes.hpp"
#include "model/model_handler.hpp"

#include "auxiliary/test_env.hpp"

#include <memory>
#include <vector>
#include <iostream>

bool TestText_1()
{
    // Create new model
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1"));

    // Add shell object to the model
    auto shell_id = model_handler->GenerateShellObject(nullptr, "Shell");
    ShellObject& shell_object = model_handler->GetShellObject(shell_id);

    {
        // Shell data
        std::vector<glm::vec3> points;
        std::vector<glm::ivec3> indices;
        GenerateSphere(glm::vec3(0, 0, 0), 2.4, points, indices);
        std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

        // Load data to previous created object
        shell_object.AppendData(points, colors, indices);
    }

    // Add text object to the model
    auto text_id = model_handler->GenerateTextObject(nullptr, "Text");
    TextObject& text_object = model_handler->GetTextObject(text_id);

    text_object.SetFontNameAndFontSize(get_fonts_resources_path() + "DejaVuSansMono-Bold.ttf", 45);
    unsigned int s_text_id = text_object.AddStaticText(L"(-: StaticText test :-)", glm::vec4(1, 0, 0, 0), 50, 200);

    text_object.SetFontNameAndFontSize(get_fonts_resources_path() + "/FreeSerifItalic.ttf", 24);
    unsigned int d_text_id = text_object.AddDynamicText(L"(-: DynamicText test :-)", glm::vec4(0, 0, 1, 0), 10, 30);

    // Create view and attach model to it
    return RunWithinTestEnv(model_handler->GetModel(), std::string(__FUNCTION__));
}

void RunTextTests()
{
    std::cout << "Text tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if(all)
    {
        TestText_1();
    }
    else
    {
    }
    std::cout << std::endl;
}