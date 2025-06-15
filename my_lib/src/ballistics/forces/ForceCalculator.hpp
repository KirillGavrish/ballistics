//
// Created by Kirill Gavrish on 26.02.2025.
//

#ifndef FORCECALCULATOR_HPP
#define FORCECALCULATOR_HPP

#include <tuple>
#include "ballistics/types/Types.hpp"

template <typename CentralForce, typename ... OtherForces>
class ForceCalculator
{
    CentralForce centralForce;
    std::tuple<OtherForces ...> otherForces;
public:
    ForceCalculator(CentralForce const &centralForce_, OtherForces const &...otherForces_)
        : centralForce(centralForce_), otherForces(otherForces_ ...)
    {}
    CentralForce getCentralForce() const { return centralForce; }
    std::tuple<OtherForces ...> getOhterForces() const { return otherForces; }

    template <typename SatelliteParameters, typename Parameters>
    [[nodiscard]] Vector3d calcForce(State const &state, SatelliteParameters const &satelliteParameters,
                                     Parameters const &parameters) const
    {
        auto const summator = [&state, &satelliteParameters, &parameters] (auto const &...forces) -> Vector3d
        {
            if constexpr (std::tuple_size_v<std::tuple<OtherForces...>> != 0) {
                return (forces.calcForce(state, satelliteParameters, parameters) + ...).eval();
            }
            return Vector3d::Zero();
        };
        Vector3d const central{centralForce.calcForce(state, satelliteParameters, parameters)};
        Vector3d const otherForcesResultant{std::apply(summator, otherForces)};
        return (central + otherForcesResultant).eval();
    }
};
#endif //FORCECALCULATOR_HPP
