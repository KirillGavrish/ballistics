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
    static constexpr std::size_t stages = 4;
    static constexpr std::array<double, stages> c = {0.0, 0.5, 0.5, 1.0};
    static constexpr std::array<double, stages> b = {1.0/6, 1.0/3, 1.0/3, 1.0/6};
    static constexpr std::array<double, stages> b_error = {-1.0/6, 1.0/3, 1.0/3, -1.0/6};

    static constexpr std::array<std::array<double, stages-1>, stages> a = {
        std::array<double, 3>{0.0, 0.0, 0.0},
        std::array<double, 3>{0.5, 0.0, 0.0},
        std::array<double, 3>{0.0, 0.5, 0.0},
        std::array<double, 3>{0.0, 0.0, 1.0}
    };
};

struct StepControl
{
    double minStep;
    double maxStep;
    double tolerance;
    double safetyFactor;
};

template <typename ButcherTable>
class NumericalMethod
{
    ButcherTable butcherTable;
    StepControl stepControl;
public:
    NumericalMethod(ButcherTable const& bt, StepControl const &stepControl_)
        : butcherTable(bt), stepControl(stepControl_)
    {}

    template <typename Parameters, typename RHS, typename Step>
    typename RHS::State makeStep(typename RHS::State const &current, Parameters const &arg, Step const &h,
                                 RHS const &rhs, double &errorEstimate) const
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
        State error = State::Zero();
        for (std::size_t i = 0; i < ButcherTable::stages; ++i)
        {
            result = result + h * k[i] * ButcherTable::b[i];
            error = error + h * k[i] * ButcherTable::b_error[i];
        }
        errorEstimate = error.norm();
        return result;
    }

    template <typename Parameters, typename RHS, typename Step>
    typename RHS::State integrate(typename RHS::State const &initial, Parameters const &argBegin,
                                  Parameters const &argEnd, Step const &initialH, RHS const &rhs) const
    {
        using State = typename RHS::State;
        State tmp = initial;
        Parameters arg = argBegin;
        Step h = initialH;
        while (arg.t < argEnd.t)
        {
            double error;
            State newState = makeStep(tmp, arg, h, rhs, error);
            if (error < stepControl.tolerance || h <= stepControl.minStep)
            {
                tmp = newState;
                arg = arg + h;
                if (error > 0)
                {
                    double scale = stepControl.safetyFactor * std::pow(stepControl.tolerance / error, 0.2);
                    scale = std::min(2., std::max(0.1, scale));
                    h = std::min(stepControl.maxStep, std::max(stepControl.minStep, h * scale));
                }
                else {
                    h = std::min(stepControl.maxStep, h * 2.);
                }
            }
            else
            {
                double scale = stepControl.safetyFactor * std::pow(stepControl.tolerance / error, 0.2);
                h = std::max(stepControl.minStep, h * std::max(0.1, scale));
            }
            if (arg.t + h > argEnd.t) {
                h = argEnd.t - arg.t;
            }
        }
        return tmp;
    }
};
#endif //NUMERICMETHODS_HPP
