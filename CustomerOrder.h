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
#include "Utilities.h"
#include "Station.h"

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

namespace sdds{

struct Item
{
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder{
    
    std::string m_name{};
    std::string m_product{};
    size_t m_cntItem{};
    Item** m_lstItem{};
    static size_t m_widthField;
    
public:
    CustomerOrder(){};
    CustomerOrder(const std::string line);
    CustomerOrder(const CustomerOrder& src); //throw exception
    CustomerOrder operator=(const CustomerOrder& src) = delete;
    CustomerOrder(CustomerOrder&& src) noexcept; //promise no exception
    CustomerOrder& operator=(CustomerOrder&& src) noexcept;
    ~CustomerOrder();
    
    bool isOrderFilled() const; //returns true if all the items in the order have been filled; false otherwise
    bool isItemFilled(const std::string& itemName) const; // returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true.
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
    
    
};
} //sdds

#endif
