//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_AIRPORT_H
#define PROJETO_2_AIRPORT_H

#include <string>

class Airport {
public:
    Airport();
    Airport(std::string code);
    Airport(const std::string &code,const std::string name,const std::string city,const std::string country,
                     double latitude , double longitude);

    //Getters
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    double getLongitude() const;
    double getLatitude() const;

    //setters
    void setCode(const std::string& newCode);
    void setName(const std::string& newName);
    void setCity(const std::string& newCity);
    void setCountry(const std::string& newCountry);
    void setLongitude(double newLongitude);
    void setLatitude(double newLatitude);
    bool operator==(const Airport& other) const;
    void operator=(const Airport& other);
    //std::ostream& operator<<(std::ostream& stream, const Airport& airport); not working n sei pq

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
    size_t operator()(const Airport& airport) const {
        size_t airportCode = std::hash<std::string>{}(airport.getCode());
        return airportCode; // Combine the hashes appropriately
    }
};
#endif //PROJETO_2_AIRPORT_H
