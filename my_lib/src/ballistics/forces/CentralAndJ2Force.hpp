//
// Created by Kirill Gavrish on 27.04.2025.
//

#ifndef CENTRALANDJ2FORCE_HPP
#define CENTRALANDJ2FORCE_HPP

#include <cmath>
#include "ballistics/types/Types.hpp"

template <typename SatelliteParameters>
class CentralAndJ2Force
{
    SatelliteParameters const satelliteParameters;
    double static constexpr mu = 3986e+11;
    double static constexpr J2 = 1.082e-3;
    double static constexpr Rev = 6378137;
public:
    CentralAndJ2Force(SatelliteParameters const &satelliteParameters_)
        : satelliteParameters(satelliteParameters_)
    {}

    [[nodiscard]] double static gravityParameter() {return mu;}
    template <typename Parameters>
    [[nodiscard]] Vector3d calcForce(State const &state, Parameters const &parameters) const;
};

inline double pow(double x, int const exp)
{
    for (int i = 0; i < exp; ++i) {x *= x;}
    return x;
}

template <typename SatelliteParameters>
template <typename Parameters>
Vector3d CentralAndJ2Force<SatelliteParameters>::calcForce(State const &state, Parameters const &parameters) const
{
    double const &x = state.position(0);
    double const &y = state.position(1);
    double const &z = state.position(2);
    double const r = state.position.norm();
    Vector3d const main = state.position * (-mu / std::pow(r, 3));
    double constexpr alpha = 1.5 * mu * Rev * Rev * J2;
    double const r7 = pow(r, 7);
    Vector3d const corr = {
        -alpha * x * (x * x + y * y - 4 * z * z) / r7,
        -alpha * y * (x * x + y * y - 4 * z * z) / r7,
        alpha * z * (-3 * x * x - 3 * y * y + 2 * z * z) / r7
    };
    return (main + corr) * satelliteParameters.mass;
};

#endif //CENTRALANDJ2FORCE_HPP
