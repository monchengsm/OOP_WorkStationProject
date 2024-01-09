// Name: SIU MAN CHENG
// Seneca Student ID: 121104228
// Seneca email: scheng39@myseneca.ca
// Date of completion: 1 Dec 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Utilities.h"

namespace sdds{

char Utilities::m_delimiter = ',';

Utilities::Utilities(){
}

void Utilities::setFieldWidth(size_t newWidth){
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const{
    return m_widthField;
}


std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
    
    size_t tempPos = std::string::npos;
    std::string tempString;
    
    tempPos = str.find(m_delimiter, next_pos);
    
    if(tempPos==next_pos){
        more = false;
        throw "Delimiter is found at next_pos!";
        
    }
    
    else if(tempPos!=std::string::npos){
        tempString = str.substr(next_pos, tempPos - next_pos);
        tempString = tempString.substr(tempString.find_first_not_of(" "), tempString.find_last_not_of(" ") -tempString.find_first_not_of(" ") + 1);//remove spaces
        // "___abc___"
        //     x = 3
        //     e = 5 + 1
        next_pos = tempPos+1;
        more = true;
        
    }
        
    else if(tempPos==std::string::npos){
        //delimiter not find: last word
        tempString = str.substr(next_pos);
        tempString = tempString.substr(tempString.find_first_not_of(" "), tempString.find_last_not_of(" ") + 1);
        more = false;
        
    }
        
    if (m_widthField < tempString.length()) {
        m_widthField = tempString.length();
    }
    
    return tempString;
}

void Utilities::setDelimiter(char newDelimiter){
    
    m_delimiter = newDelimiter;
    
}


char Utilities::getDelimiter(){
    return m_delimiter;
}

} //sdds

