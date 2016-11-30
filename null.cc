#include <sol.hpp>
#include <iostream>

// a cpp function returns nullptr
const char* nullOrNumber(int x)
{
    if (x == 42) {
        return nullptr;
    }
    return "forty two";
}

int main()
{
    sol::state lua;
    lua["pow"] = nullOrNumber;
    lua.script("result = pow(42)");
}
