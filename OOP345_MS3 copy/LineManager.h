// Name: SIU MAN CHENG
// Seneca Student ID: 121104228
// Seneca email: scheng39@myseneca.ca
// Date of completion: 1 Dec 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

namespace sdds{

class LineManager{
    
    std::vector<Workstation*> m_activeLine{};
    size_t m_cntCustomerOrder{};
    Workstation* m_firstStation{};
    
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
   // ~LineManager();
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};
    
} //sdds

#endif
