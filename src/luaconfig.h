#ifndef _LUA_CONFIG_H_
#define _LUA_CONFIG_H_

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

#include <lua.hpp>

class LuaConfig
{
public:
    LuaConfig();
    LuaConfig(const std::string &file);
    ~LuaConfig();

public:
    template <typename T>
    T get(const std::string &key);

private:
    std::string m_file;
    lua_State *m_L{nullptr};

private:
    void init_lua();
    void load_file(const std::string &file);
    void push_value_from_table(const std::string &key); // e.g. "a.b.c"
};

LuaConfig::LuaConfig()
{
    init_lua();
}

LuaConfig::LuaConfig(const std::string &file)
{
    init_lua();
    load_file(file);
}

LuaConfig::~LuaConfig()
{
    if (m_L)
    {
        lua_close(m_L);
        m_L = nullptr;
    }
}

void LuaConfig::init_lua()
{
    m_L = luaL_newstate();
    if (!m_L)
    {
        throw std::runtime_error("Failed to create Lua state");
    }
    luaL_openlibs(m_L);
}

void LuaConfig::load_file(const std::string &file)
{
    if (luaL_dofile(m_L, file.c_str()) != LUA_OK)
    {
        std::string err = lua_tostring(m_L, -1);
        lua_pop(m_L, 1);
        throw std::runtime_error("Failed to load file: " + file + ", error: " + err);
    }
}

template <typename T>
T LuaConfig::get(const std::string &key)
{
    static_assert(sizeof(T) == 0, "Unsupported type for LuaConfig::get");
    throw std::runtime_error("Unsupported type for LuaConfig::get");
}

template <>
int LuaConfig::get<int>(const std::string &key)
{
    push_value_from_table(key);
    if (!lua_isnumber(m_L, -1))
    {
        lua_pop(m_L, 1);
        throw std::runtime_error("Lua value:" + key + " is not an int");
    }
    int val = lua_tointeger(m_L, -1);
    lua_pop(m_L, 1);
    return val;
}

template <>
float LuaConfig::get<float>(const std::string &key)
{
    push_value_from_table(key);
    if (!lua_isnumber(m_L, -1))
    {
        lua_pop(m_L, 1);
        throw std::runtime_error("Lua value:" + key + " is not a float");
    }
    float val = static_cast<float>(lua_tonumber(m_L, -1));
    lua_pop(m_L, 1);
    return val;
}

template <>
double LuaConfig::get<double>(const std::string &key)
{
    push_value_from_table(key);
    if (!lua_isnumber(m_L, -1))
    {
        lua_pop(m_L, 1);
        throw std::runtime_error("Lua value:" + key + " is not a double");
    }
    double val = lua_tonumber(m_L, -1);
    lua_pop(m_L, 1);
    return val;
}

template <>
std::string LuaConfig::get<std::string>(const std::string &key)
{
    push_value_from_table(key);
    if (!lua_isstring(m_L, -1))
    {
        lua_pop(m_L, 1);
        throw std::runtime_error("Lua value:" + key + " is not a string");
    }
    std::string val = lua_tostring(m_L, -1);
    lua_pop(m_L, 1);
    return val;
}

template <>
bool LuaConfig::get<bool>(const std::string &key)
{
    push_value_from_table(key);
    if (!lua_isboolean(m_L, -1))
    {
        lua_pop(m_L, 1);
        throw std::runtime_error("Lua value:" + key + " is not a bool");
    }
    bool val = lua_toboolean(m_L, -1);
    lua_pop(m_L, 1);
    return val;
}

void LuaConfig::push_value_from_table(const std::string &key)
{
    size_t start = 0;
    size_t end = key.find('.');
    std::vector<std::string> keys;

    while (end != std::string::npos)
    {
        keys.emplace_back(key.substr(start, end - start));
        start = end + 1;
        end = key.find('.', start);
    }
    keys.emplace_back(key.substr(start));

    lua_getglobal(m_L, keys[0].c_str());

    for (size_t i = 1; i < keys.size(); ++i)
    {
        if (keys[i].find('[') != std::string::npos) // key="data[i]"
        {
            size_t bracketPos = keys[i].find('[');
            std::string field = keys[i].substr(0, bracketPos);
            int index = std::stoi(keys[i].substr(bracketPos + 1, keys[i].size() - bracketPos - 2));
            index += 1; // if index==0 then i+=1 (lua array begin index ==1)

            lua_getfield(m_L, -1, field.c_str());
            lua_remove(m_L, -2);
            if (!lua_istable(m_L, -1))
            {
                lua_pop(m_L, 1);
                throw std::runtime_error("Expected a table in path: " + key);
            }
            lua_rawgeti(m_L, -1, index);
            lua_remove(m_L, -2);
        }
        else
        {
            lua_getfield(m_L, -1, keys[i].c_str());
            lua_remove(m_L, -2);
        }
    }
}

#endif