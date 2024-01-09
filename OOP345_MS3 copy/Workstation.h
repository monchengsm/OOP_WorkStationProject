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
#include <deque>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

namespace sdds{

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    
class Workstation : public Station{
    std::deque<CustomerOrder> m_orders{};
    Workstation* m_pNextStation{};
    
public:
    Workstation(const std::string& src);
    //~Workstation();
    Workstation(const Workstation& src) = delete;
    Workstation(Workstation&& src) = delete;
    Workstation& operator=(const Workstation& src) = delete;
    Workstation& operator=(Workstation&& src) = delete;
    
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
};
    
} //sdds

#endif
