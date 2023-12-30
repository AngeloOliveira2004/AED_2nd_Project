#ifndef PROJETO_2_AIRLINE_H
#define PROJETO_2_AIRLINE_H

#include <string>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callSign;
    std::string country;

public:
    /**
     * @brief Default constructor for the Airline class.
     * @details Time complexity: O(1)
     */
    Airline();

    /**
     * @brief Parameterized constructor for the Airline class.
     * @param code The airline code.
     * @param name The name of the airline.
     * @param callSign The airline's call sign.
     * @param country The country to which the airline belongs.
     * @details Time complexity: O(1)
     */
    Airline(const std::string code, const std::string name, const std::string callSign, const std::string country);

    /**
     * @brief Getter function for retrieving the airline code.
     * @return The airline code.
     * @details Time complexity: O(1)
     */
    std::string getCode() const;

    /**
     * @brief Getter function for retrieving the name of the airline.
     * @return The name of the airline.
     * @details Time complexity: O(1)
     */
    std::string getName() const;

    /**
     * @brief Getter function for retrieving the call sign of the airline.
     * @return The call sign of the airline.
     * @details Time complexity: O(1)
     */
    std::string getCallSign() const;

    /**
     * @brief Getter function for retrieving the country to which the airline belongs.
     * @return The country of the airline.
     * @details Time complexity: O(1)
     */
    std::string getCountry() const;

    /**
     * @brief Overloaded equality operator for comparing two airlines.
     * @param other Another Airline object to compare with.
     * @return True if the airline codes are equal, false otherwise.
     * @details Time complexity: O(1)
     */
    bool operator==(const Airline& other) const;
};

template <>
struct std::hash<Airline> {
    /**
     * @brief Hash function for the Airline class.
     * @param airline The Airline object to hash.
     * @return The hash value for the Airline based on their code.
     * @details Time complexity: O(1)
     */
    size_t operator()(const Airline& airline) const {
        size_t airlineCode = std::hash<std::string>{}(airline.getCode());
        return airlineCode; // Combine the hashes appropriately
    }
};

#endif //PROJETO_2_AIRLINE_H
