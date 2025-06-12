//
// Created by Kirill Gavrish on 04.03.2025.
//

#ifndef CENTRALFORCE_HPP
#define CENTRALFORCE_HPP

#include "ballistics/types/Vector.hpp"
#include "GeographicLib/GravityModel.hpp"

template <typename SatelliteParameters>
class CentralForce
{
    SatelliteParameters const satelliteParameters;
    GeographicLib::GravityModel gravityModel;

public:
    CentralForce(std::string const &filePath, SatelliteParameters const &satelliteParameters_)
        : satelliteParameters(satelliteParameters_), gravityModel("egm2008", filePath)
    {}

    [[nodiscard]] double gravityParameter() const {return gravityModel.MassConstant();};
    [[nodiscard]] Vector3d calcForce(State const &state,
                                     SatelliteParameters const &satelliteParameters) const;
};

template<typename SatelliteParameters>
Vector3d CentralForce<SatelliteParameters>::calcForce(State const &state,
                                                      SatelliteParameters const &satelliteParameters) const
{
    const Eigen::Quaternion eci2ecef = satelliteParameters.eci2ecef;
    const Vector3d posECEF = eci2ecef._transformVector(state.position);

    double ax, ay, az;
    gravityModel.V(posECEF(0), posECEF(1), posECEF(2), ax, ay, az);

    auto const accECEF = Vector3d{ax, ay, az};

    return eci2ecef.conjugate()._transformVector(accECEF) * satelliteParameters.mass;
}

#endif //CENTRALFORCE_HPP
