#ifndef PARSEEOP_HPP
#define PARSEEOP_HPP

#include <filesystem>
#include "ballistics/conversions/EOPContainer.hpp"

[[nodiscard]] EOPContainer parseEOP(std::filesystem::path const &path);

#endif //PARSEEOP_HPP
