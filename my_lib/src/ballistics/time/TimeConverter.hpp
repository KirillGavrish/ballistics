#ifndef TIMECONVERTER_HPP
#define TIMECONVERTER_HPP
#include "Time.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"
#include "sofa/sofa.h"

using UT1 = Time<Scale::UT1>;
using UTC = Time<Scale::UTC>;
using TT  = Time<Scale::TT>;
using TCB = Time<Scale::TCB>;
using TCG = Time<Scale::TCG>;
using TDB = Time<Scale::TDB>;
using TAI = Time<Scale::TAI>;

template <typename DutContainer>
class TimeConverter {

    DutContainer const &dutContainer_;
public:
    TimeConverter(DutContainer const &);
    [[nodiscard]] double dut(UTC const &mjDay) const;

    template <Scale ScaleTo, Scale ScaleFrom>
    [[nodiscard]] Time<ScaleTo> convert(Time<ScaleFrom> const &) const;

    template <typename, typename>
    [[nodiscard]] Time<Scale::UT1> static convert(UTC const &t)
    {
        double jDay, jDayPart;
        int const sofaError = static_cast<int>(iauUtcut1(t.jDay(),t.jDayPart(), dut(t.mjDay()), &jDay, &jDayPart));

        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert UTC to UT1!");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::UTC> convert(UT1 const &t) const
    {
        UTC const utcTmp{t.jDay(), t.jDayPart()};
        double const Dut = dut(utcTmp + (- dutContainer_.dut(utcTmp.mjDay()))/86400);
        double jDay, jDayPart;
        int const sofaError = static_cast<int>(iauUt1utc(t.jDay(),t.jDayPart(), Dut, &jDay, &jDayPart));

        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert UT1 to UTC!");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::TDB> static convert(TCB const &t)
    {
        double jDay, jDayPart;
        int const sofaError = static_cast<int>(iauTcbtdb(t.jDay(),t.jDayPart(), &jDay, &jDayPart));

        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TCB to TDB!");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::TAI> static convert(UTC const &t)
    {
        double jDay, jDayPart;
        int const sofaError = static_cast<int>(iauUtctai(t.jDay(),t.jDayPart(), &jDay, &jDayPart));

        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert UTC to TAI!.");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::TT> static convert(TAI const &t)
    {
        double jDay, jDayPart;
        int const sofaError = static_cast<int>(iauTaitt(t.jDay(),t.jDayPart(), &jDay, &jDayPart));
        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TAI to TT!.");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::TT> static convert(UTC const &t)  {
        return convert<Scale::TT>(convert<Scale::TAI>(t));
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::TDB> static convert(TT const &t)
    {
        double jDay, jDayPart;
        double const dtr = 0.001657*std::sin(6.24 + 0.017202 * (t.jDay() + t.jDayPart()) - 2451545);

        int const sofaError = static_cast<int>(iauTttdb(t.jDay(),t.jDayPart(), dtr, &jDay, &jDayPart));
        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TT to TDB!.");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
    [[nodiscard]] Time<Scale::TT> static convert(TDB const &t)
    {
        double jDay, jDayPart;
        double const dtr = 0.001657*std::sin(6.24 + 0.017202 * (t.jDay() + t.jDayPart()) - 2451545);

        int const sofaError = static_cast<int>(iauTdbtt(t.jDay(),t.jDayPart(), dtr, &jDay, &jDayPart));
        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TDB to TT!.");
        }
        return {jDay, jDayPart};
    }
    template <typename, typename>
    [[nodiscard]] Time<Scale::TT> static convert(TCG const &t)
    {
        double jDay, jDayPart;

        int const sofaError = static_cast<int>(iauTcgtt(t.jDay(),t.jDayPart(), &jDay, &jDayPart));
        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TCG to TT!.");
        }
        return {jDay, jDayPart};
    }
    template <typename, typename>
    [[nodiscard]] Time<Scale::TAI> static convert(TT const &t)
    {
        double jDay, jDayPart;

        int const sofaError = static_cast<int>(iauTttai(t.jDay(),t.jDayPart(), &jDay, &jDayPart));
        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TT to TAI!.");
        }
        return {jDay, jDayPart};
    }

    template <typename, typename>
     [[nodiscard]] Time<Scale::UTC> static convert(TAI const &t)
    {
        double jDay, jDayPart;

        int const sofaError = static_cast<int>(iauTaiutc(t.jDay(),t.jDayPart(), &jDay, &jDayPart));
        if (sofaError == -1) {
            throw BallisticsException("Sofa Error! Unable to convert TAI to UTC!.");
        }
        return {jDay, jDayPart};
    }
    template <typename, typename>
    [[nodiscard]] Time<Scale::UTC> static convert(TT const &t)  {
        return convert<Scale::UTC>(convert<Scale::TAI>(t));
    }
    template <typename, typename>
    [[nodiscard]] Time<Scale::UTC> static convert(TCG const &t)  {
        return convert<Scale::UTC>(convert<Scale::TT>(t));
    }
}; // TimeCoverter

template<typename DutContainer>
TimeConverter<DutContainer>::TimeConverter(DutContainer const &dutContainer)
    : dutContainer_(dutContainer)
{}

template <typename DutContainer>
double TimeConverter<DutContainer>::dut(UTC const &mjDay) const {return dutContainer_.dut(mjDay);};

#endif //TIMECONVERTER_HPP
