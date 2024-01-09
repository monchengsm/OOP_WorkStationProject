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
#include "Workstation.h"

namespace sdds{

std::deque<CustomerOrder> pending{};
std::deque<CustomerOrder> completed{};
std::deque<CustomerOrder> incomplete{};

void Workstation::fill(std::ostream& os)
{
    if (!m_orders.empty()) {
        m_orders.front().fillItem(*this, os);
    }
}
bool Workstation::attemptToMoveOrder()
{
    if (!m_orders.empty()) {
        if (m_orders.front().isItemFilled(this->getItemName())) {
            if (m_pNextStation)
                *m_pNextStation+= std::move(m_orders.front());
            else
                completed.push_back(std::move(m_orders.front()));

            m_orders.pop_front();
            return true;
        }
        else if (this->getQuantity()) {
            if (m_pNextStation)
                *m_pNextStation+= std::move(m_orders.front());
            else {
                incomplete.push_back(std::move(m_orders.front()));
            }
            m_orders.pop_front();
            return true;
        }
    }
    return false;
}
Workstation* Workstation::getNextStation() const
{
    return m_pNextStation;
}
void Workstation::display(std::ostream& os) const
{
    os << getItemName() << "--> ";
    if (m_pNextStation != nullptr)
        os << m_pNextStation->getItemName() << std::endl;
    else
        os << "End of Line" << std::endl;
}
Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
{
    m_orders.push_back(std::move(newOrder));
    return *this;
}
}

}//sdds


