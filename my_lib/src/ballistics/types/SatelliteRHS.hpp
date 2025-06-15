#ifndef NUMERICMETHODRHS_HPP
#define NUMERICMETHODRHS_HPP

#include "ballistics/forces/ForceCalculator.hpp"
#include "ballistics/types/Types.hpp"

template <typename CentralForce, typename ... OtherForces>
class SatelliteRHS
{
    ForceCalculator<CentralForce, OtherForces...> forceCalculator;
    SatelliteParameters satelliteParameters;
public:
    SatelliteRHS(ForceCalculator<CentralForce, OtherForces...> const &otherForceCalculator, SatelliteParameters const &otherSatelliteParameters)
        : forceCalculator(otherForceCalculator), satelliteParameters(otherSatelliteParameters)
    {}

    using State = State;
    using ArgType = Parameters;

    [[nodiscard]] Vector3d evaluate(State const &state, ArgType const &arg) const {
        return forceCalculator.calcForce(state, satelliteParameters, arg) / satelliteParameters.mass;
    }


};
#endif //NUMERICMETHODRHS_HPP
