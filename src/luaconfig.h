#ifndef _LUA_CONFIG_H_
#define _LUA_CONFIG_H_

#include <string>

class LuaConfig
{
private:
    /* data */
public:
    LuaConfig() = default;
    LuaConfig(const std::string& file){};
    ~LuaConfig() = default;
};

#endif