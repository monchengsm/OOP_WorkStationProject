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
#include "CustomerOrder.h"


namespace sdds{

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(const std::string line){
        Utilities tempObj;
        
        size_t next_pos = 0;
        bool more = true;
        size_t item_pos = 0;
        std::string tempField{};
        
        
        m_name = tempObj.extractToken(line, next_pos, more);
        m_product = tempObj.extractToken(line, next_pos, more);
        
        item_pos = next_pos; //for 2 looping
        //count
        while(more==true){
            tempField = tempObj.extractToken(line, next_pos, more);
            m_cntItem++;
        }
    
        //assign memory to 1st layer
        m_lstItem = new Item*[m_cntItem];
    
        //reset
        more = true;
    
        //list of items
        //Item** m_lstItem{};
        for(size_t i = 0; i<m_cntItem; i++){
            m_lstItem[i] = new Item(tempObj.extractToken(line, item_pos, more));
        }
        
        m_widthField = m_widthField > tempObj.getFieldWidth()? m_widthField:tempObj.getFieldWidth();
    
         
    }


CustomerOrder::~CustomerOrder(){
    
    
    if(m_lstItem){
        //1st layer
        for(size_t i = 0; i< m_cntItem; i++){
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
        }
        //2nd layer
        delete[] m_lstItem;
        m_lstItem = nullptr;
        
    }
    
}

CustomerOrder::CustomerOrder(const CustomerOrder& src){
    throw std::string("Copy Constructor should not be called!");
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{

        *this = std::move(src);

}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept{
    if(this!=&src){
        if(m_lstItem){
            //1st layer
            for(size_t i = 0; i< m_cntItem; i++){
                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }
            //2nd layer
            delete[] m_lstItem;
            m_lstItem = nullptr;
        }
       
        m_cntItem = src.m_cntItem;
        m_lstItem = src.m_lstItem;
        m_name = src.m_name;
        m_product = src.m_product;
       
        
        src.m_lstItem = nullptr;
        src.m_name = "";
        src.m_product = "";
        src.m_cntItem = 0;
        
    }
    return *this;
}


void CustomerOrder::fillItem(Station& station, std::ostream& os){
    bool isFilled = false;
    for(size_t i = 0; i< m_cntItem; i++){
        
        std::cout << i << ": m_itemName: " << m_lstItem[i]->m_itemName << "  station.getItemName: " << station.getItemName() << std::endl;
        
        if(m_lstItem[i]->m_itemName == station.getItemName()){
            
            if(m_lstItem[i]->m_isFilled==false && isFilled == false){
                
                if(station.getQuantity()>0 ){
                    isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity(); //--
                    
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                else{
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
            }
        
    }
}

/*Thomas
 void CustomerOrder::fillItem(Station& station, std::ostream& os) {
         bool filled = false;
         for (size_t i = 0; i < m_cntItem && !filled; ++i)
         {
             if (m_lstItem[i]->m_isFilled == filled && m_lstItem[i]->m_itemName == station.getItemName())
             {
                 if (station.getQuantity() > 0)
                 {
                     station.updateQuantity();
                     m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                     //m_lstItem[i]->m_serialNumber++;
                     m_lstItem[i]->m_isFilled = true;
                     filled = true;
                     os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                 }
                 else
                 {
                     os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                 }
             }
         }
     }
*/

bool CustomerOrder::isOrderFilled() const{
    bool isFilled = true;
    
    for(size_t i = 0; i< m_cntItem; i++){
        if(m_lstItem[i]->m_isFilled == false){
            isFilled = false;
        }
    }
    return isFilled;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const{
    bool isFilled = true;
    
    for(size_t i = 0; i< m_cntItem; i++){
        if(m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false){
            isFilled = false; //If the item doesn't exist in the order, this query returns true.
        }
    }
    return isFilled;
}

void CustomerOrder::display(std::ostream& os) const{
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] " ;
            os << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName;
            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
}



}//sdds


