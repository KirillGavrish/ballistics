#ifndef SOLARRADIATIONPRESSURE_HPP
#define SOLARRADIATIONPRESSURE_HPP

#include "ballistics/types/Types.hpp"
#include "ballistics/time/Time.hpp"
#include "ballistics/ephemeris/EphemerisCalculator.hpp"

class СylindricalShadowFunction
{
    double static constexpr earthRadius = 6378140;
    double static constexpr moonRadius = 1737400;
public:
    double static calcShadowFunction(Vector3d const &position, Vector3d const &sunPosition, Vector3d const &moonPosition);
};

template <typename EphemerisCalculator, typename ShadowModel>
class SolarPressure {
    EphemerisCalculator ephemerisCalculator;
    ShadowModel shadowModel;
public:
    SolarPressure(EphemerisCalculator const &ephemerisCalculator_, ShadowModel const &shadowModel)
        : ephemerisCalculator(ephemerisCalculator_), shadowModel(shadowModel)
    {}

    template <typename SatelliteParameters, typename Parameters>
    [[nodiscard]] Vector3d calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                     Parameters const &parameters) const;
};

template <typename EphemerisCalculator, typename ShadowModel>
template <typename SatelliteParameters, typename Parameters>
Vector3d SolarPressure<EphemerisCalculator, ShadowModel>::calcForce(State const &state,
                                                                    SatelliteParameters const &satelliteParameters,
                                                                    Parameters const &parameters) const
{
    Vector3d const sunPosition = ephemerisCalculator.calcPosition(parameters.tdb(), CelestialBodies::EARTH, CelestialBodies::SUN);
    Vector3d const moonPosition = ephemerisCalculator.calcPosition(parameters.tdb(), CelestialBodies::EARTH, CelestialBodies::MOON);
    Vector3d const n = (sunPosition - state.position).normalized();
    double const satelliteSunDistance = (sunPosition - state.position).norm();
    double const AU = ephemerisCalculator.au();
    return parameters.TSI * AU * AU / (satelliteSunDistance * satelliteSunDistance) * n *
           shadowModel.calcShadowFunction(parameters.tdb(), state.position, sunPosition, moonPosition)
           / ephemerisCalculator.clight() * satelliteParameters.Area;
}

#endif //SOLARRADIATIONPRESSURE_HPP
