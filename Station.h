// Name: SIU MAN CHENG
// Seneca Student ID: 121104228
// Seneca email: scheng39@myseneca.ca
// Date of completion: 1 Dec 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"

#ifndef SDDS_STATION_H
#define SDDS_STATION_H



namespace sdds{

class Station{
    size_t m_stationID{};
    std::string m_name{}; //name of item
    std::string m_desc{};
    size_t m_serialNumber{};  //next serial number
    size_t m_item{}; //number of item
    
    static size_t m_widthField;
    static size_t id_generator; //+1 after assign
    
public:
    Station(const std::string line);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
    
    
};

} //sdds

#endif
