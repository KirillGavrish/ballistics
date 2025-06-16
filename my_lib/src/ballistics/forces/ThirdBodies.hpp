#ifndef THIRDBODIES_HPP
#define THIRDBODIES_HPP

#include "ballistics/types/Types.hpp"
#include "ballistics/ephemeris/EphemerisCalculator.hpp"

template <typename EphemerisCalculator>
class ThirdBodies
{
    EphemerisCalculator ephemerisCalculator;
    std::vector<CelestialBodies> bodies;

    std::unordered_map<CelestialBodies, double> static constexpr GM_PARAMS =
    {
        {CelestialBodies::SUN, 1.32712440018e20},
        {CelestialBodies::MERCURY, 2.2032e13},
        {CelestialBodies::VENUS, 3.24859e14},
        {CelestialBodies::EARTH, 3.986004418e14},
        {CelestialBodies::MOON, 4.9048695e12},
        {CelestialBodies::MARS, 4.282837e13},
        {CelestialBodies::JUPITER, 1.26686534e17},
        {CelestialBodies::SATURN, 3.7931187e16},
        {CelestialBodies::URANUS, 5.793939e15},
        {CelestialBodies::NEPTUNE, 6.836529e15},
        {CelestialBodies::PLUTO, 8.71e11}
    };
public:
    ThirdBodies(EphemerisCalculator const &ephemerisCalculator_, std::vector<CelestialBodies> const &bodies_)
        : ephemerisCalculator(ephemerisCalculator_), bodies(bodies_)
    {}

    template <typename SatelliteParameters, typename Parameters>
    Vector3d calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                       Parameters const &parameters) const
    {
        Vector3d totalForce = Vector3d::Zero();
        for (auto const body : bodies)
        {
            Vector3d const bodyPosition = ephemerisCalculator.calcPosition(parameters.tdb(), CelestialBodies::EARTH, body);
            Vector3d const r = bodyPosition - state.position;
            double const distance = r.norm();
            double const gm = GM_PARAMS.at(body);
            Vector3d const force = gm * satelliteParameters.mass *
                             (r / (distance * distance * distance) -
                             bodyPosition / (bodyPosition.norm() * bodyPosition.norm() * bodyPosition.norm()));
            totalForce += force;
        }
        return totalForce;
    }
};
#endif //THIRDBODIES_HPP
