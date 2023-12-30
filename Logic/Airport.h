#ifndef PROJETO_2_AIRPORT_H
#define PROJETO_2_AIRPORT_H

#include <string>

class Airport {
public:
    /**
     * @brief Default constructor for the Airport class.
     * @details Time complexity: O(1)
     */
    Airport();

    /**
     * @brief Constructor for the Airport class with only a code parameter.
     * @param code The airport code.
     * @details Time complexity: O(1)
     */
    Airport(std::string code);

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
    Airport(const std::string &code, const std::string name, const std::string city, const std::string country,
            double latitude, double longitude);

    // Getters

    /**
     * @brief Getter function for retrieving the airport code.
     * @return The airport code.
     * @details Time complexity: O(1)
     */
    std::string getCode() const;

    /**
     * @brief Getter function for retrieving the name of the airport.
     * @return The name of the airport.
     * @details Time complexity: O(1)
     */
    std::string getName() const;

    /**
     * @brief Getter function for retrieving the city where the airport is located.
     * @return The city of the airport.
     * @details Time complexity: O(1)
     */
    std::string getCity() const;

    /**
     * @brief Getter function for retrieving the country to which the airport belongs.
     * @return The country of the airport.
     * @details Time complexity: O(1)
     */
    std::string getCountry() const;

    /**
     * @brief Getter function for retrieving the longitude of the airport.
     * @return The longitude of the airport.
     * @details Time complexity: O(1)
     */
    double getLongitude() const;

    /**
     * @brief Getter function for retrieving the latitude of the airport.
     * @return The latitude of the airport.
     * @details Time complexity: O(1)
     */
    double getLatitude() const;

    // Setters

    /**
     * @brief Setter function for updating the airport code.
     * @param newCode The new airport code.
     * @details Time complexity: O(1)
     */
    void setCode(const std::string &newCode);

    /**
     * @brief Setter function for updating the name of the airport.
     * @param newName The new name of the airport.
     * @details Time complexity: O(1)
     */
    void setName(const std::string &newName);

    /**
     * @brief Setter function for updating the city where the airport is located.
     * @param newCity The new city of the airport.
     * @details Time complexity: O(1)
     */
    void setCity(const std::string &newCity);

    /**
     * @brief Setter function for updating the country to which the airport belongs.
     * @param newCountry The new country of the airport.
     * @details Time complexity: O(1)
     */
    void setCountry(const std::string &newCountry);

    /**
     * @brief Setter function for updating the longitude of the airport.
     * @param newLongitude The new longitude of the airport.
     * @details Time complexity: O(1)
     */
    void setLongitude(double newLongitude);

    /**
     * @brief Setter function for updating the latitude of the airport.
     * @param newLatitude The new latitude of the airport.
     * @details Time complexity: O(1)
     */
    void setLatitude(double newLatitude);

    /**
     * @brief Overloaded equality operator for comparing two airports.
     * @param other Another Airport object to compare with.
     * @return True if the airport codes are equal, false otherwise.
     * @details Time complexity: O(1)
     */
    bool operator==(const Airport &other) const;

    /**
     * @brief Overloaded assignment operator for copying the attributes of another airport.
     * @param other Another Airport object to copy from.
     * @details Time complexity: O(1)
     */
    void operator=(const Airport &other);

private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double longitude;
    double latitude;
};

template <>
struct std::hash<Airport> {
    /**
     * @brief Hash function for the Airport class.
     * @param airport The Airport object to hash.
     * @return The hash value for the Airport based on their code.
     * @details Time complexity: O(1)
     */
    size_t operator()(const Airport &airport) const {
        size_t airportCode = std::hash<std::string>{}(airport.getCode());
        return airportCode; // Combine the hashes appropriately
    }
};

#endif //PROJETO_2_AIRPORT_H
