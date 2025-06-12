//
// Created by Kirill Gavrish on 26.02.2025.
//

#ifndef FORCECALCULATOR_HPP
#define FORCECALCULATOR_HPP

#include <tuple>
#include "ballistics/types/Vector.hpp"
#include "ballistics/time/Time.hpp"

struct SatelliteParameters {};

template <SatelliteParameters, typename CentralForce, typename ... OtherForces>
class ForceCalculator
{
    CentralForce centralForce;
    std::tuple<OtherForces ...> otherForces;
    SatelliteParameters satelliteParameters;
public:
    ForceCalculator(CentralForce const &centralForce_, OtherForces const &...otherForces_,
                    SatelliteParameters const &satelliteParameters_)
        : centralForce(centralForce_), otherForces(otherForces_), satelliteParameters(satelliteParameters_)
    {}

    [[nodiscard]] Vector3d calcResultantForce(State const &state)
    {
        auto const summator = [&state, this] (auto const &...forces)
        {
            if constexpr (std::tuple_size_v<std::tuple<OtherForces...>> != 0) {
                return (forces.calcForce(state, this->satelliteParameters) + ...).eval();
            }
            return Vector3d::Zero();
        };
        Vector3d const centralForce_{centralForce.calcForce(state, satelliteParameters)};
        Vector3d const otherForcesResultant{std::apply(summator, otherForces)};
        return (centralForce_ + otherForcesResultant).eval();
    }
};
#endif //FORCECALCULATOR_HPP
