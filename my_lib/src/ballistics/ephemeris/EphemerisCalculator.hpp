#ifndef EPHEMERISCALCULATOR_HPP
#define EPHEMERISCALCULATOR_HPP

#include "calceph.h"
#include "ballistics/exceptions/BallisticsException.hpp"
#include "ballistics/time/Time.hpp"
#include "ballistics/types/Types.hpp"

enum class CelestialBodies
{
    MERCURY = 1,
    VENUS = 2,
    EARTH = 3,
    MARS = 4,
    JUPITER = 5,
    SATURN = 6,
    URANUS = 7,
    NEPTUNE = 8,
    PLUTO = 9,
    MOON = 10,
    SUN = 11,
    SOLAR_SYSTEM_BARYCENTER = 12,
    EARTH_MOON_BARYCENTER = 13
};

using TDB = Time<Scale::TDB>;

class EphemerisCalculator {
    t_calcephbin *calceph;

public:
    EphemerisCalculator(std::string const& path) {
        calceph = calceph_open(path.c_str());
        if (!calceph) {
            throw BallisticsException("Can't open ephemeris file!");
        }
    }
    ~EphemerisCalculator() { calceph_close(calceph); }

    [[nodiscard]] Vector3d calcPosition(TDB, CelestialBodies origin, CelestialBodies body) const;
    [[nodiscard]] Vector6d calcState(TDB, CelestialBodies origin, CelestialBodies body) const;
    [[nodiscard]] double au() const;
    [[nodiscard]] double clight() const;
};

#endif //EPHEMERISCALCULATOR_HPP
