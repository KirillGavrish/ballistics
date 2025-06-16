//
// Created by Kirill Gavrish on 27.04.2025.
//

#ifndef CENTRALANDJ2FORCE_HPP
#define CENTRALANDJ2FORCE_HPP

#include <cmath>
#include "ballistics/types/Types.hpp"

class CentralAndJ2Force
{
    double static constexpr mu = 3986e+11;
    double static constexpr J2 = 1.082e-3;
    double static constexpr Rev = 6378137;
public:
    [[nodiscard]] double static gravityParameter() { return mu; }
    template <typename SatelliteParameters, typename Parameters>
    [[nodiscard]] Vector3d calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                     Parameters const &parameters) const;
};

template <typename SatelliteParameters, typename Parameters>
Vector3d CentralAndJ2Force::calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                      Parameters const &parameters) const
{
    double const &x = state.position(0);
    double const &y = state.position(1);
    double const &z = state.position(2);
    double const r = state.position.norm();
    Vector3d const main = (state.position * (-mu / std::pow(r, 3))).eval();
    double constexpr alpha = 1.5 * mu * Rev * Rev * J2;
    double const r7 = std::pow(r, 7);
    Vector3d const corr(-alpha * x * (x * x + y * y - 4 * z * z) / r7,
                        -alpha * y * (x * x + y * y - 4 * z * z) / r7,
                        alpha * z * (-3 * x * x - 3 * y * y + 2 * z * z) / r7);
    return (-(main + corr) * satelliteParameters.mass).eval();
};

#endif //CENTRALANDJ2FORCE_HPP
