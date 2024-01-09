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
#include <fstream>

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H



namespace sdds{

class Utilities{
    size_t m_widthField{1};
    static char m_delimiter;
    
public:
    Utilities();
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    
    static void setDelimiter(char newDelimiter);
    static char getDelimiter();
    
};

} //sdds

#endif
