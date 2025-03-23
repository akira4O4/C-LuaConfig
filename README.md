# C-LuaConfig

**Easy** C\C++ LuaConfig lib

---

## Feat
- Only one file
- Support: C\C++
- Support: int,float,double,std::string,bool
- Support: array index calls e.g."a.b.c[0]"

---

## Usage

### 1.Install Lua

```bash
sudo apt install lua5.3
```

### 2.Edit your ```config.lua```

```lua
name="C-LuaConfig"

config = {
    window = {
        width = 1280,
        height = 720,
    },
    title = "My Application",
    fullscreen = false,
    colors = {
        background = {0.1, 0.2, 0.3},
        text = {1.0, 2.0, 3.0},
    },
}
```

### 3.Edit your ```main.cc```
```cpp
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

```