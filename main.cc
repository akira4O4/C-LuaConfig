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
    auto fullscreen = config->get<bool>("config.fullscreen");
    auto rgb0 = config->get<float>("config.colors.background[0]");

    std::cout << name << std::endl;
    std::cout << width << std::endl;
    std::cout << height << std::endl;
    std::cout << title << std::endl;
    std::cout << fullscreen << std::endl;
    std::cout << rgb0 << std::endl;

    return 0;
}
