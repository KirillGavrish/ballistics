#include "BallisticsException.hpp"

BallisticsException::BallisticsException(char const *message)
    : message_(message)
{}
BallisticsException::BallisticsException(std::string const &message)
    : BallisticsException(message.c_str())
{}
const char *BallisticsException::what() const noexcept {return message_.c_str();}