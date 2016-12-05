#include <sol.hpp>
#include <iostream>
#include <boost/numeric/conversion/cast.hpp>
#include "strong_typedef.hpp"

constexpr const double COORDINATE_PRECISION = 1e6;

OSRM_STRONG_TYPEDEF(int32_t, FixedLatitude)
OSRM_STRONG_TYPEDEF(int32_t, FixedLongitude)
OSRM_STRONG_TYPEDEF(double, FloatLatitude)
OSRM_STRONG_TYPEDEF(double, FloatLongitude)

inline FixedLatitude toFixed(const FloatLatitude floating)
{
    const auto latitude = static_cast<double>(floating);
    const auto fixed = boost::numeric_cast<std::int32_t>(latitude * COORDINATE_PRECISION);
    return FixedLatitude{fixed};
}

inline FixedLongitude toFixed(const FloatLongitude floating)
{
    const auto longitude = static_cast<double>(floating);
    const auto fixed = boost::numeric_cast<std::int32_t>(longitude * COORDINATE_PRECISION);
    return FixedLongitude{fixed};
}

inline FloatLatitude toFloating(const FixedLatitude fixed)
{
    const auto latitude = static_cast<std::int32_t>(fixed);
    const auto floating = boost::numeric_cast<double>(latitude / COORDINATE_PRECISION);
    return FloatLatitude{floating};
}

inline FloatLongitude toFloating(const FixedLongitude fixed)
{
    const auto longitude = static_cast<std::int32_t>(fixed);
    const auto floating = boost::numeric_cast<double>(longitude / COORDINATE_PRECISION);
    return FloatLongitude{floating};
}

struct Coordinate
{
    double lon;
    double lat;
};

template <class T> double latToDouble(T const &object)
{
    return static_cast<double>(object.lat);
}
template <class T> double lonToDouble(T const &object)
{
    return static_cast<double>(object.lon);
}

int main()
{

    sol::state lua;
    lua.script("function segment_func (source) val = source.lon() return 0 end");

    lua.new_usertype<Coordinate>(
        "Coordinate", "lon", &lonToDouble<Coordinate>, "lat", &latToDouble<Coordinate>);

    Coordinate a_coord = {5.000, 6.500};

    sol::function segment_function = lua["segment_func"];
    segment_function(a_coord);

    return 0;
}
