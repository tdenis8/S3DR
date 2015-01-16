#include "tests/model_tests.hpp"
#include "tests/text_tests.hpp"
#include "tests/point_tests.hpp"
#include "tests/line_tests.hpp"
#include "tests/shell_tests.hpp"

#include "tests/light_tests.hpp"

#include "auxiliary/resources_handler.hpp"

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

void error(const std::string& error_message, unsigned int severity)
{
    if(severity != 0)
    {
        std::cout << error_message << std::endl;
    }
    if(severity == 2)
    {
        exit(1);
    }
}

std::vector<std::string> pack_arguments(int argc, char const* argv[])
{
    std::vector<std::string> res;
    for(int i = 0; i != argc; ++i)
    {
        res.push_back(argv[i]);
    }
    return res;
}

int main(int argc, char const* argv[])
{
    auto args = pack_arguments(argc, argv);
    error("\nError: missing resources path!\n", args.size() == 2 ? 0 : 2);
    set_main_resource_path(args[1]);

    RunModelTests();
    RunTextTests();
    RunPointTests();
    RunLineTests();
    RunShellTests();
    RunLightTests();

    return 0;
}