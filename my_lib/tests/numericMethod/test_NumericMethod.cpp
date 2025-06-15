#include <Paths.hpp>
#include "ballistics/forces/CentralForce.hpp"
#include "gtest/gtest.h"
#include "ballistics/types/Types.hpp"
#include "ballistics/types/SatelliteRHS.hpp"
#include "ballistics/conversions/QuaternionConvertion.hpp"
#include "ballistics/forces/ForceCalculator.hpp"
#include "ballistics/forces/CentralAndJ2Force.hpp"
#include "ballistics/numeric_methods/NumericalMethod.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;
static constexpr double eps1000 = std::numeric_limits<double>::epsilon() * 1000;


TEST(NumericalMethod, adequacyGEO)
{
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const centralForce(resourcesPath() / "CentralForce/");
    ForceCalculator const forceCalculator(centralForce);
    State const current  = {{42157000, 0, 0}, {3074, 0, 0}};
    SatelliteRHS const rhs(forceCalculator, satelliteParameters);
    RK4Table const butcherTable;
    NumericalMethod const method(butcherTable);
    State const calculated = method.integrate(current, parameters, parameters + 1, 1/24/60, rhs);
    //std::cout.precision(16);
    //std::cout << calculated.position.norm() << std::endl;
    ASSERT_NEAR(42157000, calculated.position.norm(), 1000);
}