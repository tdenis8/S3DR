#include "text_tests.hpp"

#include "misc.hpp"

#include "asset/3D_shapes.hpp"
#include "model/model_handler.hpp"

#include <memory>
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>

bool TestText_1()
{
    std::unique_ptr<ModelHandler> model_handler(new ModelHandler("Model1"));

    auto shell_id = model_handler->GenerateShellObject(nullptr, "Shell");
    ShellObject &shell_object = model_handler->GetShellObject(shell_id);

    {
        std::vector<glm::vec3> points;
        std::vector<glm::ivec3> indices;
        GenerateSphere(glm::vec3(0, 0, 0), 2.4, points, indices);
        std::vector<glm::vec4> colors(points.size(), glm::vec4(0.1, 1.0, 0.0, 1.0));

        shell_object.AppendData(points, colors, indices);
    }

    auto text_id = model_handler->GenerateTextObject(nullptr, "Text");
    TextObject &text_object = model_handler->GetTextObject(text_id);

    text_object.SetFontNameAndFontSize("/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono-Bold.ttf", 45);
    unsigned int s_text_id = text_object.AddStaticText(L"(-: StaticText test :-)", glm::vec4(1, 0, 0, 0), 50, 200);

    text_object.SetFontNameAndFontSize("/usr/share/fonts/truetype/freefont/FreeSerifItalic.ttf", 24);
    unsigned int d_text_id = text_object.AddDynamicText(L"(-: DynamicText test :-)", glm::vec4(0, 0, 1, 0), 10, 30);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    return RunWithinTestEnv(&model_handler->GetModel(),
                            std::string(__FUNCTION__),
                            [&]()
                            {
        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        {
            text_object.UpdateDynamicText(d_text_id, std::to_wstring(1000.0 / double(nbFrames)) + L" ms/frame");
            nbFrames = 0;
            lastTime += 1.0;
        }
    });
}

void RunTextTests()
{
    std::cout << "Text tests: " << std::endl;
    std::cout << "--------------------------" << std::endl;
    auto all = true;
    if (all)
    {
        TestText_1();
    }
    else
    {
    }
    std::cout << std::endl;
}