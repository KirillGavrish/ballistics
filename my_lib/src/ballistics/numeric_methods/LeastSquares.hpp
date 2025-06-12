//
// Created by Kirill Gavrish on 29.04.2025.
//

#ifndef LEASTSQUARES_HPP
#define LEASTSQUARES_HPP

#include <limits>
#include "ballistics/types/Vector.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;

template <typename State, typename NumericMethod>
class LeastSquares
{
    std::vector<State> observation;
    std::vector<double> observationTime;
    std::vector<Eigen::Matrix<double, State::size(), State::size()>> W;
    NumericMethod numericMethod;
    std::size_t maxIt;
public:
    [[nodiscard]] std::size_t N() const { return observation.size(); };
    LeastSquares(std::vector<State> const &observation_,
                 std::vector<Eigen::Matrix<double, State::size(), State::size()>> const &W_, std::size_t const maxIt_)
        : observation(observation_), W(W_), maxIt(maxIt_)
    {}

    std::tuple<State, Eigen::Matrix<double, State::size(), State::size()>> calc() const
    {
        for (std::size_t it = 0; it < maxIt; ++it) {
            State deltaX;
            State const deltaX0 = observation[0] * 10e-8;
            std::vector<Eigen::Matrix<double, State::size(), State::size()>> A(N, Eigen::Matrix<double, State::size(),
                                                                                State::size()>::Zeros());
            std::vector<Eigen::Vector<double, State::size()>> b(N, Eigen::Vector<double, State::size()>::Zeros());
            std::vector<State> computed;
            State X0 = observation[0];
            for (std::size_t k = 0; k < State::size(); ++k)
            {
                X0[k] += deltaX0[k];
                computed.push_back(X0);
                for (std::size_t n = 0; n < N()-1; ++n)
                {
                    computed.push_back(numericMethod(computed[n], observationTime[n+1],
                                       observationTime[n+1] - observationTime[n], NumericMethod::RHS));
                    for (std::size_t j = 0; j < State::size(); ++j)
                    {
                        A[n](k, j) = (computed[n][j] - observation[n][j]) / deltaX0[k];
                        b[n][j] = observation[n][j] - computed[n][j];
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
            auto RMS = [this, &b]() -> Eigen::Matrix<double, State::size(), 1>
            {
                auto tmp = Eigen::Matrix<double, State::size(), 1>::Zeros();
                for (std::size_t n = 0; n < N(); ++n) {
                    tmp += b.transpose() * W[n] * b[n] / N;
                }
                return tmp;
            };
            Eigen::Matrix<double, State::size(), State::size()> const P = calcP();
            deltaX = P * calcATWb();
            X0 = X0 + deltaX;
            if (std::sqrt(RMS()) < eps10) {
                return {X0, P};
            }
        }
        throw BallisticsException("The method did not converge!");
    }


};

#endif //LEASTSQUARES_HPP
