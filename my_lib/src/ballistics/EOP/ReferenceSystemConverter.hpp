#ifndef REFERENCESYSTEMCONVERTER_HPP
#define REFERENCESYSTEMCONVERTER_HPP

#include "ballistics/EOP/EOPContainer.hpp"
#include "sofa/sofa.h"
#include "Eigen/Dense"
#include "ballistics/time/TimeConverter.hpp"

enum class ReferenceSystem {GCRS = 3, ITRS = 5};


class ReferenceSystemConverter
{
    EOPContainer const &eopContainer_;
    TimeConverter<EOPContainer> const &timeConverter_;
public:
    ReferenceSystemConverter (EOPContainer const &EOPcontainer)
        : eopContainer_(EOPcontainer), timeConverter_(EOPcontainer)
    {}

    template <ReferenceSystem RSto, ReferenceSystem RSFrom, Scale scale>
    [[nodiscard]] Eigen::Quaternion<double> convert(Time<scale> const &);


    template <> template <>
    [[nodiscard]] Eigen::Quaternion<double> convert<ReferenceSystem::ITRS, ReferenceSystem::GCRS>(Time<Scale::TCG> const& t) const
    {
        auto const utc = timeConverter_.convert<Scale::UTC>(t);
        auto const ut1 = timeConverter_.convert<Scale::UT1>(utc);
        double const era = iauEra00(ut1.jDay(), ut1.jDayPart());

        double const dX = eopContainer_.dX(utc.mjDay());
        double const dY = eopContainer_.dY(utc.mjDay());

        double X, Y;
        iauXy06(t.jDay(), t.jDayPart(), &X, &Y);

        double const s = iauS06(t.jDay(), t.jDayPart(), X, Y);
        double c2i[3][3];
        iauC2ixys(X+dX, Y+dY, s, c2i);

        double const xp = eopContainer_.x(utc.mjDay());
        double const yp = eopContainer_.y(utc.mjDay());
        double const s1 = iauSp00(t.jDay(), t.jDayPart());
        double pom[3][3];
        iauPom00(xp, yp, s1, pom);

        double c2t[3][3];
        iauC2tcio(c2i, era, pom, c2t);

        Eigen::Matrix<double, 3, 3> const c2tMatrix{
            {c2t[0][0], c2t[0][1], c2t[0][2]},
            {c2t[1][0], c2t[1][1], c2t[1][2]},
            {c2t[2][0], c2t[2][1], c2t[2][2]}
        };

        return Eigen::Quaternion<double>{c2tMatrix};
    }
};

#endif //REFERENCESYSTEMCONVERTER_HPP
