#include "Airline.h"

Airline::Airline() {}

Airline::Airline(const std::string code, const std::string name, const std::string callSign, const std::string country) :
        code(code), name(name), callSign(callSign), country(country) {}

std::string Airline::getCode() const {
    return code;
}

std::string Airline::getName() const {
    return name;
}

std::string Airline::getCallSign() const {
    return callSign;
}

std::string Airline::getCountry() const {
    return country;
}

bool Airline::operator==(const Airline &other) const {
    return this->code == other.code;
}


