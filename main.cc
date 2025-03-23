#include "src/luaconfig.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string file = "../config.lua";
    auto config = new LuaConfig(file);

    auto name = config->get<std::string>("name");
    auto width = config->get<int>("config.window.width");
    auto height = config->get<int>("config.window.height");
    auto title = config->get<std::string>("config.title");
    auto enable = config->get<bool>("config.enable");
    auto rgb0 = config->get<int>("config.colors.rgb[0]");
    auto rgba1 = config->get<float>("config.colors.rgba[1]");

    std::cout << name << std::endl;
    std::cout << width << std::endl;
    std::cout << height << std::endl;
    std::cout << title << std::endl;
    std::cout << enable << std::endl;
    std::cout << rgb0 << std::endl;
    std::cout << rgba1 << std::endl;

    return 0;
}
