#include <osmium/osm.hpp>
#include <sol.hpp>

namespace sol
{
template <> struct is_container<osmium::Node> : std::false_type
{
};
template <> struct is_container<osmium::Way> : std::false_type
{
};
}

namespace sol
{
namespace meta
{
template <> struct has_key_value_pair<osmium::Node> : std::false_type
{
};
template <> struct has_key_value_pair<osmium::Way> : std::false_type
{
};
}
}

int main()
{
    sol::state lua;
    lua.new_usertype<osmium::Node>("Node",
                                   "location",
                                   &osmium::Node::location,
                                   "get_value_by_key",
                                   &osmium::Node::get_value_by_key,
                                   "id",
                                   &osmium::Node::id);

    osmium::Node foo;

    lua.script("function Fun (x) return end");
    sol::function Fun = lua["Fun"];
    Fun(foo);

    return 0;
}
