#include "DutContainer.hpp"
#include "ballistics/interpolation/Interpolant.hpp"

DutContainer::DutContainer(EOPContainer const &eopContainer)
    : mjDays_(eopContainer.mjDays()), duts_(eopContainer.duts())
{}

double DutContainer::dut(double const mjDay) const {return Interpolant{mjDays_, duts_}.evaluate(mjDay);}
