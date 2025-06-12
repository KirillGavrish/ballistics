#ifndef SOLARRADIATIONPRESSURE_HPP
#define SOLARRADIATIONPRESSURE_HPP

#include "ballistics/types/Vector.hpp"
#include "ballistics/time/Time.hpp"
#include "ballistics/ephemeris/EphemerisCalculator.hpp"

class СylindricalShadowFunction
{
    double static constexpr earthRadius = 6378140;
    double static constexpr moonRadius = 1737400;
public:
    double static calcShadowFunction(Time<Scale::TDB> const &, Vector3d const &position, Vector3d const &sunPosition,
                                     Vector3d const &moonPosition);
};

template <typename EphemerisCalculator, typename ShadowModel, typename SatelliteParameters>
class SolarPressure {
    EphemerisCalculator ephemerisCalculator;
    ShadowModel shadowModel;
    double TSI;
    Time<Scale::TDB> tdb;
public:
    SolarPressure(ShadowModel const &shadowModel)
        : shadowModel(shadowModel)
    {}

    [[nodiscard]] Vector3d calcForce(State const &state,
                                     SatelliteParameters const &satelliteParameters) const;
};

template <typename EphemerisCalculator, typename ShadowModel, typename SatelliteParameters>
Vector3d SolarPressure<EphemerisCalculator, ShadowModel, SatelliteParameters>::calcForce(State const &state,
                                                                                         SatelliteParameters const &satelliteParameters)
                                                                                         const
{
    Vector3d const sunPosition = ephemerisCalculator.calcPosition(tdb, CelestialBodies::EARTH, CelestialBodies::SUN);
    Vector3d const moonPosition = ephemerisCalculator.calcPosition(tdb, CelestialBodies::EARTH, CelestialBodies::MOON);
    Vector3d const n = (sunPosition - state.position).normalized();
    double const satelliteSunDistance = (sunPosition - state.position).norm();
    double const AU = ephemerisCalculator.au();
    return TSI * AU * AU / (satelliteSunDistance * satelliteSunDistance) * n *
           shadowModel.calcShadowFunction(tdb, state.position, sunPosition, moonPosition)
           / ephemerisCalculator.clight() * satelliteParameters.Area;
}

#endif //SOLARRADIATIONPRESSURE_HPP
