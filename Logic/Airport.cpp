//
// Created by jose-costa on 12/23/23.
//

#include "Airport.h"


Airport::Airport(const std::string &code,const std::string name,const std::string city,const std::string country,
                 double longitude, double latitude)
        : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

Airport::Airport(std::string  code) : code(std::move(code)) , name(" ") , city(" ") , latitude(0.0) , longitude(0.0) {}

//Getters
std::string Airport::getCode() const {
    return code;
}

std::string Airport::getName() const {
    return name;
}

std::string Airport::getCity() const {
    return city;
}

std::string Airport::getCountry() const {
    return country;
}

double Airport::getLongitude() const {
    return longitude;
}

double Airport::getLatitude() const {
    return latitude;
}

//setters
void Airport::setCode(const std::string& newCode) {
    code = newCode;
}

void Airport::setName(const std::string& newName) {
    name = newName;
}

void Airport::setCity(const std::string& newCity) {
    city = newCity;
}

void Airport::setCountry(const std::string& newCountry) {
    country = newCountry;
}

void Airport::setLongitude(double newLongitude) {
    longitude = newLongitude;
}

void Airport::setLatitude(double newLatitude) {
    latitude = newLatitude;
}

bool Airport::operator==(const Airport &other) const {
    return code == other.code;
}

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

bool Airport::operator!=(const Airport& other) const {
    if((code != other.code)&&(name != other.name)&&(city != other.city)&&(country != other.country)&&(latitude != other.latitude)&&(longitude != other.longitude)){
        return true;
    }
    return false;
}
