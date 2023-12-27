//
// Created by jose-costa on 12/23/23.
//

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
    Airline();
    Airline(const std::string code,const std::string name,const std::string callSign,const std::string country);

    std::string getCode() const;
    std::string getName() const;
    std::string getCallSign() const;
    std::string getCountry() const;

    bool operator==(const Airline& other) const;

};

template <>
struct std::hash<Airline> {
    /**
     * @param airline The Airline object to hash.
     * @return The hash value for the Airline based on their code.
     */
    size_t operator()(const Airline& airline) const {
        size_t airlineCode = std::hash<std::string>{}(airline.getCode());
        return airlineCode; // Combine the hashes appropriately
    }
};

#endif //PROJETO_2_AIRLINE_H
