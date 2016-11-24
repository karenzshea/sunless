#include <osmium/osm.hpp>
#include <osmium/handler.hpp>
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

    struct Handler : osmium::handler::Handler {
        sol::state& lua;

        Handler(sol::state &s) : lua(s){
        // register lua function
        lua.script("(function handsy(n) return 0 end)");
        };

        void handleNode(osmium::Node &node)
        {
            // retrieve lua function
            sol::function handsy = lua["handsy"];
            // call lua function with variable type
            handsy(node);
        };
    };

    return 0;
}
