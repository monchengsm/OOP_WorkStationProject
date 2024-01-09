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
#include "Station.h"


namespace sdds{


size_t Station::m_widthField = 0;
size_t Station::id_generator = 1;

Station::Station(const std::string line){
    Utilities tempObj;
    
    size_t next_pos = 0;
    bool more = true;
    
    
    m_name = tempObj.extractToken(line, next_pos, more);
    m_serialNumber = std::stoll(tempObj.extractToken(line, next_pos, more));
    m_item =  std::stoll(tempObj.extractToken(line, next_pos, more));
    
    m_widthField = m_widthField > tempObj.getFieldWidth()? m_widthField:tempObj.getFieldWidth();
    m_desc = tempObj.extractToken(line, next_pos, more);

    m_stationID = id_generator;
    id_generator++;
     
    
}

const std::string& Station::getItemName() const{
    return m_name;
}

size_t Station::getNextSerialNumber(){
    
    size_t temp{};
    temp = m_serialNumber;
    m_serialNumber++;
    
    return temp;
}

size_t Station::getQuantity() const{
    return m_item;
}


void Station::updateQuantity(){
    if(m_item>0){
        m_item--;
    }
}



void Station::display(std::ostream& os, bool full) const{
    if(!full){
        os << std::setw(3) << std::setfill('0') << m_stationID << " | ";
        os << std::left << std::setw(int(m_widthField)) << std::setfill(' ') << m_name <<  " | ";
        os << std::setw(6) << std::right << std::setfill('0') << m_serialNumber <<  " | ";
    }
    else{
        os << std::setw(3) << std::setfill('0') << m_stationID << " | ";  
        os << std::left <<  std::setw(int(m_widthField)) << std::setfill(' ') << m_name <<  " | ";
        os << std::setw(6) << std::right << std::setfill('0') << m_serialNumber <<  " | ";
        os << std::right << std::setw(4) << std::setfill(' ') << m_item <<  " | ";
        os << m_desc;
    }
    
    os << std::endl;
}


} //sdds

