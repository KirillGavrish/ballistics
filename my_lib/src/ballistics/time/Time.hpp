#pragma once
#include <cmath>

enum class Scale{UT1 = 0, UTC = 1, TT = 2, TCG = 3, TCB = 4, TDB = 5, TAI = 6};

template <Scale scale>
class Time {
    double jDay_;
    double jDayPart_;
    
public:
    [[nodiscard]] double jDay() const;
    [[nodiscard]] double jDayPart() const;
    [[nodiscard]] double mjDay() const;

    Time(double jDay = 0, double jDayPart = 0) noexcept;
    auto operator<=>(Time const &other) const noexcept = default;
};

template <Scale scale>
double Time<scale>::jDay() const {return jDay_;};
template <Scale scale>
double Time<scale>::jDayPart() const {return jDayPart_;};
template<Scale scale>
double Time<scale>::mjDay() const {return jDay_ + jDayPart_ - 2400000.5;};

template <Scale scale>
Time<scale>::Time(double const jDay, double const jDayPart) noexcept
        : jDay_(jDay), jDayPart_(jDayPart)
{}

template <Scale scale>
Time<scale> operator-(Time<scale> const & t1, double const deduction)
{
    double ded_int;
    double ded_partial = std::modf(deduction, &ded_int);
    return t1.jDayPart() - ded_partial >= 0
        ? Time<scale>(t1.jDay() - ded_int, t1.jDayPart() - ded_partial)
        : Time<scale>(t1.jDay() - ded_int - 1, 1 + t1.jDayPart() - ded_partial);
}

template <Scale scale>
Time<scale> operator+(Time<scale> const & t1, double const increment)
{
    double ded_int;
    double ded_partial = std::modf(increment, &ded_int);
    return t1.jDayPart() + ded_partial >= 1
        ? Time<scale>(t1.jDay() + ded_int + 1, t1.jDayPart() - ded_partial - 1)
        : Time<scale>(t1.jDay() + ded_int, t1.jDayPart() - ded_partial);
}

template <Scale scale>
double operator-(Time<scale> const & t1, Time<scale> const & t2)
{
    return t1.jDay() + t1.jDayPart() - (t2.jDay() + t2.jDayPart());
}


