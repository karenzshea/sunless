#define SOL_CHECK_ARGUMENTS
#include <iostream>
#include <sol.hpp>

struct Foo
{
    void SetName(std::string &name, const char *value)
    {
        if (value == nullptr)
        {
            name.clear();
        }
        else
        {
            name = std::string(value);
        }
    }
    const char *GetName() const { return name.c_str(); }

    std::string name;
};

int main()
{

    sol::state lua;
    lua.script("function segment_func (foo) \
            foo.name = \"poodle\" \
            foo.name = nil \
            return 0 \
            end");

    lua.new_usertype<Foo>("foo", "name", sol::property(&Foo::SetName));

    sol::function segment_function = lua["segment_func"];
    lua.script(R"(segment_func("name", nil))");

    return 0;
}
