//
// Created by Kirill Gavrish on 13.02.2025.
//

#ifndef NUMERICMETHODS_HPP
#define NUMERICMETHODS_HPP

#include <array>
#include "Eigen/Dense"



class Oscillator
{
    using ArgType = double;
    static constexpr unsigned int size_ = 2;
    using vec = Eigen::Vector<double, size_>;
    [[nodiscard]] vec evaluate(ArgType const &, vec const &) const;
};

struct RK4Table
{
    static constexpr size_t stages = 4;
    static constexpr std::array<double, stages> c = {0.0, 0.5, 0.5, 1.0};
    static constexpr std::array<double, stages> b = {1.0/6, 1.0/3, 1.0/3, 1.0/6};

    static constexpr std::array<std::array<double, stages-1>, stages> a = {
        std::array<double, 3>{0.0, 0.0, 0.0},
        std::array<double, 3>{0.5, 0.0, 0.0},
        std::array<double, 3>{0.0, 0.5, 0.0},
        std::array<double, 3>{0.0, 0.0, 1.0}
    };
};

template <typename ButcherTable>
class NumericalMethod
{
    ButcherTable butcherTable;
public:
    NumericalMethod(ButcherTable const& bt) :
        butcherTable(bt)
    {}

    template <typename Parameters, typename RHS, typename Step>
    typename RHS::State makeStep(typename RHS::State const &current, Parameters const &arg, Step const &h,
                                 RHS const &rhs) const
    {
        using State = typename RHS::State;
        std::array<State, ButcherTable::stages> k;
        k[0] = State{rhs.evaluate(current, arg)};
        for (std::size_t i = 1; i < ButcherTable::stages; ++i)
        {
            State sum = State::Zero();
            for (std::size_t j = 0; j < i; ++j) {
                sum = sum + k[j] * ButcherTable::a[i][j];
            }
            State tmp = current + h * sum;
            k[i] = State{rhs.evaluate(tmp, arg + h * ButcherTable::c[i])};
        }
        State result = current;
        for (std::size_t i = 0; i < ButcherTable::stages; ++i) {
            result = result + h * k[i] * ButcherTable::b[i];
        }
        return result;
    }

    template <typename Parameters, typename RHS, typename Step>
    typename RHS::State integrate(typename RHS::State const &current, Parameters const &argBegin,
                                  Parameters const &argEnd, Step const &h, RHS const &rhs) const
    {
        using State = typename RHS::State;
        State tmp = current;
        for (Parameters t = argBegin; t.t < argEnd.t; t = t + h)
        {
            tmp = makeStep(tmp, t, h, rhs);
            if ((t + h).t > argEnd.t)
            {
                tmp = makeStep(tmp, t, argEnd - t, rhs);
                break;
            }
        }
        return tmp;
    }
};
#endif //NUMERICMETHODS_HPP
