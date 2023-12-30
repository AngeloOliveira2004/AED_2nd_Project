#include "Airport.h"

/**
 * @brief Default constructor for the Airport class.
 * @details Time complexity: O(1)
 */
Airport::Airport(): code(""), name(" "), city(" "), latitude(0.0), longitude(0.0) {}

/**
 * @brief Parameterized constructor for the Airport class.
 * @param code The airport code.
 * @param name The name of the airport.
 * @param city The city where the airport is located.
 * @param country The country to which the airport belongs.
 * @param latitude The latitude of the airport.
 * @param longitude The longitude of the airport.
 * @details Time complexity: O(1)
 */
Airport::Airport(const std::string &code, const std::string name, const std::string city, const std::string country,
                 double latitude, double longitude)
        : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

/**
 * @brief Constructor for the Airport class with only a code parameter.
 * @param code The airport code.
 * @details Time complexity: O(1)
 */
Airport::Airport(std::string code) : code(std::move(code)), name(" "), city(" "), latitude(0.0), longitude(0.0) {}

// Getters

/**
 * @brief Getter function for retrieving the airport code.
 * @return The airport code.
 * @details Time complexity: O(1)
 */
std::string Airport::getCode() const {
    return code;
}

/**
 * @brief Getter function for retrieving the name of the airport.
 * @return The name of the airport.
 * @details Time complexity: O(1)
 */
std::string Airport::getName() const {
    return name;
}

/**
 * @brief Getter function for retrieving the city where the airport is located.
 * @return The city of the airport.
 * @details Time complexity: O(1)
 */
std::string Airport::getCity() const {
    return city;
}

/**
 * @brief Getter function for retrieving the country to which the airport belongs.
 * @return The country of the airport.
 * @details Time complexity: O(1)
 */
std::string Airport::getCountry() const {
    return country;
}

/**
 * @brief Getter function for retrieving the longitude of the airport.
 * @return The longitude of the airport.
 * @details Time complexity: O(1)
 */
double Airport::getLongitude() const {
    return longitude;
}

/**
 * @brief Getter function for retrieving the latitude of the airport.
 * @return The latitude of the airport.
 * @details Time complexity: O(1)
 */
double Airport::getLatitude() const {
    return latitude;
}

// Setters

/**
 * @brief Setter function for updating the airport code.
 * @param newCode The new airport code.
 * @details Time complexity: O(1)
 */
void Airport::setCode(const std::string &newCode) {
    code = newCode;
}

/**
 * @brief Setter function for updating the name of the airport.
 * @param newName The new name of the airport.
 * @details Time complexity: O(1)
 */
void Airport::setName(const std::string &newName) {
    name = newName;
}

/**
 * @brief Setter function for updating the city where the airport is located.
 * @param newCity The new city of the airport.
 * @details Time complexity: O(1)
 */
void Airport::setCity(const std::string &newCity) {
    city = newCity;
}

/**
 * @brief Setter function for updating the country to which the airport belongs.
 * @param newCountry The new country of the airport.
 * @details Time complexity: O(1)
 */
void Airport::setCountry(const std::string &newCountry) {
    country = newCountry;
}

/**
 * @brief Setter function for updating the longitude of the airport.
 * @param newLongitude The new longitude of the airport.
 * @details Time complexity: O(1)
 */
void Airport::setLongitude(double newLongitude) {
    longitude = newLongitude;
}

/**
 * @brief Setter function for updating the latitude of the airport.
 * @param newLatitude The new latitude of the airport.
 * @details Time complexity: O(1)
 */
void Airport::setLatitude(double newLatitude) {
    latitude = newLatitude;
}

/**
 * @brief Overloaded equality operator for comparing two airports.
 * @param other Another Airport object to compare with.
 * @return True if the airport codes are equal, false otherwise.
 * @details Time complexity: O(1)
 */
bool Airport::operator==(const Airport &other) const {
    return code == other.code;
}

/**
 * @brief Overloaded assignment operator for copying the attributes of another airport.
 * @param other Another Airport object to copy from.
 * @details Time complexity: O(1)
 */
void Airport::operator=(const Airport &other) {
    if (this != &other) {
        code = other.code;
        name = other.name;
        city = other.city;
        country = other.country;
        latitude = other.latitude;
        longitude = other.longitude;
    }
}
