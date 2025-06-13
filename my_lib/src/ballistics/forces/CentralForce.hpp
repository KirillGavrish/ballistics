//
// Created by Kirill Gavrish on 04.03.2025.
//

#ifndef CENTRALFORCE_HPP
#define CENTRALFORCE_HPP

#include "ballistics/types/Types.hpp"
#include "GeographicLib/GravityModel.hpp"

template <typename SatelliteParameters>
class CentralForce
{
    SatelliteParameters const satelliteParameters;
    GeographicLib::GravityModel gravityModel;
public:
    CentralForce(std::string const &filePath, SatelliteParameters const &satelliteParameters_)
        : satelliteParameters(satelliteParameters_),
          gravityModel(GeographicLib::GravityModel("egm2008", filePath))
    {}

    [[nodiscard]] double gravityParameter() const { return gravityModel.MassConstant(); }
    template <typename Parameters>
    [[nodiscard]] Vector3d calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                     Parameters const &parameters) const;
};

template <typename SatelliteParameters>
template <typename Parameters>
Vector3d CentralForce<SatelliteParameters>::calcForce(State const &state,
                                                      SatelliteParameters const &satelliteParameters,
                                                      Parameters const &parameters) const
{
    Vector3d const positionEcef = parameters.quaternionEciToEcef * state.position;
    double ax, ay, az;
    gravityModel.V(positionEcef(0), positionEcef(1), positionEcef(2), ax, ay, az);
    auto const aEcef = Vector3d(ax, ay, az);
    return parameters.quaternionEciToEcef.conjugate() * aEcef * satelliteParameters.mass;
}

#endif //CENTRALFORCE_HPP
