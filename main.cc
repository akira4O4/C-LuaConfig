#include "src/luaconfig.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string file="../config.lua";
    std::cout<<file<<std::endl; 
    auto config= new LuaConfig(file);
    
    return 0;
}
