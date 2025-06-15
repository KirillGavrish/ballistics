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

template <typename T>
class Observation
{
    std::vector<T> observation;
    std::vector<double> observationTime;
public:
    Observation(std::vector<T> const &observation_, std::vector<double> const &observationTime_)
        : observation(observation_), observationTime(observationTime_)
    {}

    T obs(std::size_t const n) const { return observation[n]; }
    T time(std::size_t const n) const { return time[n]; }
};

template <typename State, typename NumericMethod>
class LeastSquares
{
    Observation<State> data;
    std::vector<Eigen::Matrix<double, State::size(), State::size()>> W;
    NumericMethod numericMethod;
    std::size_t maxIt;
public:
    [[nodiscard]] std::size_t N() const { return data.observation.size(); }

    LeastSquares(Observation<State> const &data_, std::vector<Eigen::Matrix<double, State::size(), State::size()>> const &W_,
                 std::size_t const maxIt_)
        : data(data_), W(W_), maxIt(maxIt_)
    {}

    std::tuple<State, Eigen::Matrix<double, State::size(), State::size()>> calc() const
    {
        State X0 = data.obs(0);
        for (std::size_t it = 0; it < maxIt; ++it)
        {
            State const deltaX0 = X0 * eps1000;
            std::vector<Eigen::Matrix<double, State::size(), State::size()>> const A(N(),
                                                                                     Eigen::Matrix<double, State::size(), State::size()>::Zeros());
            std::vector<Eigen::Vector<double, State::size()>> const b(N(), Eigen::Vector<double, State::size()>::Zeros());
            std::vector<State> computed;
            for (std::size_t k = 0; k < State::size(); ++k)
            {
                State tmpX0 = X0;
                tmpX0[k] += deltaX0[k];
                computed.push_back(tmpX0);
                for (std::size_t n = 0; n < N()-1; ++n)
                {
                    computed.push_back(numericMethod(computed[n], data.time(n+1), data.time(n+1) - data.time(n),
                                       NumericMethod::RHS));
                    for (std::size_t j = 0; j < State::size(); ++j)
                    {
                        A[n](k, j) = (computed[n][j] - data.obs(n)[j]) / deltaX0[k];
                        b[n][j] = data.obs(n)[j] - computed[n][j];
                    }
                }
            }
            auto calcP = [&A, this]() -> Eigen::Matrix<double, State::size(), State::size()>
            {
                auto tmp = Eigen::Matrix<double, State::size(), State::size()>::Zeros();
                for (std::size_t n = 0; n < N(); ++n) {
                    tmp += A[n].transpose() * W[n] * A[n];
                }
                return tmp.inverse();
            };
            auto calcATWb = [&A, this, &b]() -> Eigen::Matrix<double, State::size(), 1>
            {
                auto tmp = Eigen::Matrix<double, State::size(), State::size()>::Zeros();
                for (std::size_t n = 0; n < N(); ++n) {
                    tmp += A[n].transpose() * W[n] * b[n];
                }
                return tmp;
            };
            auto RMS = [this, &b]() -> double
            {
                auto tmp = Eigen::Matrix<double, State::size(), 1>::Zeros();
                for (std::size_t n = 0; n < N(); ++n) {
                    tmp += b.transpose() * W[n] * b[n] / N;
                }
                return tmp;
            };
            auto const P = calcP();
            State deltaX = P * calcATWb();
            X0 = X0 + deltaX;
            if (std::sqrt(RMS()) < eps1000) {
                return {X0, P};
            }
        }
        throw BallisticsException("The method did not converge!");
    }
};

#endif //LEASTSQUARES_HPP
