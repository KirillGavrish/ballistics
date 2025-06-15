#include <Paths.hpp>
#include "ballistics/forces/CentralForce.hpp"
#include "gtest/gtest.h"
#include "ballistics/types/Types.hpp"
#include "ballistics/types/SatelliteRHS.hpp"
#include "ballistics/conversions/QuaternionConvertion.hpp"
#include "ballistics/forces/ForceCalculator.hpp"
#include "ballistics/forces/CentralAndJ2Force.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;
static constexpr double eps1000 = std::numeric_limits<double>::epsilon() * 1000;

TEST(SatelliteRHS, adequacyGEO)
{
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const centralForce(resourcesPath() / "CentralForce/");
    CentralAndJ2Force constexpr centralAndJ2Force;
    ForceCalculator const forceCalculator(centralForce, centralAndJ2Force);
    State const current  = {{42157000, 0, 0}, {0, 3070, 0}};
    SatelliteRHS const rhs(forceCalculator, satelliteParameters);
    Vector3d const calculated = rhs.evaluate(current, parameters);
    ASSERT_NEAR(0.224 * 2, calculated.norm(), 0.01);
}