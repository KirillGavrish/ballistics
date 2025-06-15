//
// Created by Kirill Gavrish on 04.03.2025.
//

#ifndef CENTRALFORCE_HPP
#define CENTRALFORCE_HPP

#include "ballistics/types/Types.hpp"
#include "GeographicLib/GravityModel.hpp"
#include "ballistics/conversions/QuaternionConvertion.hpp"

class CentralForce
{
    std::string filePath;
    GeographicLib::GravityModel gravityModel;
public:
    CentralForce(CentralForce const &otherCentralForce)
        : filePath(otherCentralForce.getFilePath()),
          gravityModel(GeographicLib::GravityModel("egm2008", otherCentralForce.getFilePath()))
    {}

    CentralForce(std::string const &filePath_)
        : filePath(filePath_), gravityModel(GeographicLib::GravityModel("egm2008", filePath_))
    {}

    [[nodiscard]] std::string getFilePath() const { return filePath; }
    [[nodiscard]] double gravityParameter() const { return gravityModel.MassConstant(); }
    template <typename SatelliteParameters, typename Parameters>
    [[nodiscard]] Vector3d calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                     Parameters const &parameters) const;
};

template <typename SatelliteParameters, typename Parameters>
Vector3d CentralForce::calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                 Parameters const &parameters) const
{
    Vector3d const positionEcef = QuaternionConvertion::guaternionGcrstoEcef(parameters.t) * state.position;
    double ax, ay, az;
    gravityModel.V(positionEcef(0), positionEcef(1), positionEcef(2), ax, ay, az);
    auto const aEcef = Vector3d(ax, ay, az);
    return QuaternionConvertion::guaternionGcrstoEcef(parameters.t).conjugate() * aEcef * satelliteParameters.mass;
}

#endif //CENTRALFORCE_HPP
