#include "Airline.h"

/**
 * @brief Default constructor for the Airline class.
 * @details Time complexity: O(1)
 */
Airline::Airline() {}

/**
 * @brief Parameterized constructor for the Airline class.
 * @param code The airline code.
 * @param name The name of the airline.
 * @param callSign The airline's call sign.
 * @param country The country to which the airline belongs.
 * @details Time complexity: O(1)
 */
Airline::Airline(const std::string code, const std::string name, const std::string callSign, const std::string country) :
        code(code), name(name), callSign(callSign), country(country) {}

/**
 * @brief Getter function for retrieving the airline code.
 * @return The airline code.
 * @details Time complexity: O(1)
 */
std::string Airline::getCode() const {
    return code;
}

/**
 * @brief Getter function for retrieving the name of the airline.
 * @return The name of the airline.
 * @details Time complexity: O(1)
 */
std::string Airline::getName() const {
    return name;
}

/**
 * @brief Getter function for retrieving the call sign of the airline.
 * @return The call sign of the airline.
 * @details Time complexity: O(1)
 */
std::string Airline::getCallSign() const {
    return callSign;
}

/**
 * @brief Getter function for retrieving the country to which the airline belongs.
 * @return The country of the airline.
 * @details Time complexity: O(1)
 */
std::string Airline::getCountry() const {
    return country;
}

/**
 * @brief Overloaded equality operator for comparing two airlines.
 * @param other Another Airline object to compare with.
 * @return True if the airline codes are equal, false otherwise.
 * @details Time complexity: O(1)
 */
bool Airline::operator==(const Airline &other) const {
    return this->code == other.code;
}
