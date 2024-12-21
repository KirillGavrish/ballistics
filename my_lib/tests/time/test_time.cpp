#include <limits>
#include "gtest/gtest.h"
#include "ballistics/time/Time.hpp"
#include "ballistics/files/parseEOP.hpp"
#include "Paths.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"
#include "ballistics/time/TimeConverter.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;

TEST(Time, EVALUATE) {
    auto const t = Time<Scale::UTC>{1, 0};
    EXPECT_EQ(t.jDay(), 1);
}
TEST(parseEOP, TEST_EXCEPTIONS)
{
    ASSERT_THROW(auto eopContainer = parseEOP(resourcesPath() / "eopc04_xtended.dat"), BallisticsException);
    ASSERT_NO_THROW(auto eopContainer = parseEOP(resourcesPath() / "eopc04_extended.dat"););
}

TEST(parseEOP, TEST_READ)
{
    auto const eopContainer = parseEOP(resourcesPath() / "eopc04_extended.dat");
    ASSERT_EQ(eopContainer.duts()[0], 0.3986990);
    ASSERT_EQ(eopContainer.mjDays()[1], 49719);
    ASSERT_NEAR(eopContainer.dut(49718.5), (0.3959977 + 0.3986990) / 2, eps);
}

TEST(TimeConverter, CONVERT)
{
    auto const eopContainer = parseEOP(resourcesPath() / "eopc04_extended.dat");
    auto const utc = Time<Scale::TCG>{2449718, 0.5};
    auto const converter = TimeConverter(eopContainer);
    auto const ut1 = converter.convert<Scale::UTC>(utc);
    ASSERT_EQ(ut1.jDay() + ut1.jDayPart() - (utc.jDay() + utc.jDayPart()), eopContainer.dut(utc.mjDay()));
}

