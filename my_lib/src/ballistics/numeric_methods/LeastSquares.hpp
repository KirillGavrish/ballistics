//
// Created by Kirill Gavrish on 29.04.2025.
//

#ifndef LEASTSQUARES_HPP
#define LEASTSQUARES_HPP

#include <limits>
#include "ballistics/types/Types.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;
static constexpr double eps1000 = std::numeric_limits<double>::epsilon() * 1000;

template <typename T, typename Parameters>
class Observation
{
    std::vector<T> observation;
    std::vector<Parameters> observationParameters;
public:
    Observation(std::vector<T> const &observation_, std::vector<double> const &observationTime_)
        : observation(observation_), observationParameters(observationTime_)
    {}

    T obs(std::size_t const n) const { return observation[n]; }
    Parameters params(std::size_t const n) const { return observationParameters[n]; }
};

template <typename State, std::size_t StateSize, typename Parameters, typename NumericMethod>
class LeastSquares
{
    Observation<State, Parameters> data;
    std::vector<Eigen::Matrix<double, StateSize, StateSize>> W;
    NumericMethod numericMethod;
    std::size_t maxIt;
public:
    [[nodiscard]] std::size_t N() const { return data.observation.size(); }

    LeastSquares(Observation<State, Parameters> const &data_,
                 std::vector<Eigen::Matrix<double, StateSize, StateSize>> const &W_, std::size_t const maxIt_)
        : data(data_), W(W_), maxIt(maxIt_)
    {}

    std::tuple<State, Eigen::Matrix<double, StateSize, StateSize>> calc() const
    {
        State X0 = data.obs(0);
        for (std::size_t it = 0; it < maxIt; ++it)
        {
            auto sigma = [this](std::size_t const n, std::size_t const i) -> double {
                return 1. / std::sqrt(W[n](i));
            };
            State delta = State::Zero();
            for (std::size_t i = 0; i < StateSize; ++i) {
                delta[i] = sigma(0, i) * 0.1;
            }
            std::vector<Eigen::Matrix<double, StateSize, StateSize>> const A(N(),
                                                                             Eigen::Matrix<double, StateSize, StateSize>::Zeros());
            std::vector<Eigen::Vector<double, StateSize>> const b(N(), Eigen::Vector<double, StateSize>::Zeros());
            std::vector<State> computed(N());
            for (std::size_t k = 0; k < State::size(); ++k)
            {
                computed[0] = X0;
                computed[0][k] += delta[k];
                for (std::size_t n = 1; n < N(); ++n)
                {
                    computed[n] = numericMethod.integrate(computed[n-1], data.params(n),
                                                          data.params(n) - data.params(n-1), NumericMethod::RHS);
                    for (std::size_t j = 0; j < StateSize; ++j)
                    {
                        A[n](k, j) = (computed[n][j] - data.obs(n)[j]) / delta[k];
                        b[n][j] = data.obs(n)[j] - computed[n][j];
                    }
                }
            }
            auto P = Eigen::Matrix<double, StateSize, StateSize>::Zero();
            auto ATWb = Eigen::Matrix<double, StateSize, 1>::Zero();
            Eigen::Matrix<double, StateSize, StateSize> ATW;
            for (std::size_t n = 0; n < N(); ++n)
            {
                ATW = A[n].transpose() * W[n];
                P += ATW * A[n];
                ATWb += ATW * b[n];
            }
            P = P.inverse();
            State deltaX = State(P * ATWb);
            X0 = X0 + deltaX;
            auto RMS = [this, &b]() -> double
            {
                double tmp = 0;
                for (std::size_t n = 0; n < N(); ++n) {
                    tmp += (b[n].transpose() * W[n] * b[n]).value();
                }
                return std::sqrt(tmp) / N();
            };
            if (RMS() < eps1000) {
                return {X0, P};
            }
        }
        throw BallisticsException("The method did not converge!");
    }
};

#endif //LEASTSQUARES_HPP
