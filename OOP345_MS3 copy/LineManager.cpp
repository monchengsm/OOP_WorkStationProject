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
#include <vector>
#include "LineManager.h"

namespace sdds{

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
    Utilities tempObj;
    
    size_t next_pos = 0;
    bool more = true;
    std::string templine{};
    std::string currentStationline{};
    std::string nextStationline{};
    Workstation* currentStation{};
    Workstation* nextStation{};
    
    std::ifstream fin(file);
    
    if (!fin){
        throw std::string("Unable to open LineManager file.");
    }
    
    else{
        while (std::getline(fin, templine))
        {
            next_pos = 0;
            currentStationline = tempObj.extractToken(templine, next_pos, more);
            
            std::for_each(stations.begin(), stations.end(), [&](auto each){
                if(each->getItemName() == currentStationline){
                    currentStation = each;
                }
            });
            
            
            if(more){
                nextStationline = tempObj.extractToken(templine, next_pos, more);
                
                std::for_each(stations.begin(), stations.end(), [&](auto each){
                    if(each->getItemName() == nextStationline){
                        nextStation = each;
                    }
                });
                
                currentStation->setNextStation(nextStation);
            }
            
            
            m_activeLine.push_back(currentStation);
        }
        
    }
    fin.close();
    
    //1st layer = ActiveLine
    //2nd layer = comparison activeline
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto eachActiveLine) {
            bool matchedStation = std::any_of(m_activeLine.begin(), m_activeLine.end(), [=](auto eachStation) {
                return (eachStation->getNextStation() == eachActiveLine);
            });
        
        if (matchedStation==false){
            m_firstStation = eachActiveLine;
        }
        });
    
    m_cntCustomerOrder = g_pending.size();
}

/*
LineManager::~LineManager(){
    delete m_firstStation;
}*/


void LineManager::reorderStations(){
    std::vector<Workstation*> orderedStations{};
    //orderedStations.push_back(m_firstStation); //1st station
    
    Workstation* firstStation{};
    firstStation = m_firstStation;
    
    while(firstStation){
        orderedStations.push_back(firstStation);
        firstStation = firstStation->getNextStation();
    }
    
    m_activeLine = orderedStations;
}


bool LineManager::run(std::ostream& os){
    bool result = false;
    static size_t numCount = 0;
    numCount++;
    os << "Line Manager Iteration: " << numCount << std::endl;

    if (!g_pending.empty()) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    //fill operation
    
    for(size_t i = 0; i < m_activeLine.size(); i++){
        std::cout << "What is the active line item: " << m_activeLine[i]->getItemName() << std::endl;
        m_activeLine[i]->fill(os);
    }
    
    for(size_t i = 0; i < m_activeLine.size(); i++){
        m_activeLine[i]->attemptToMoveOrder();
    }
    
    
    //for each station on the line, executes one fill operation
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto eachActiveLine) {
                eachActiveLine->fill(os);
            });

        
    //for each station on the line, attempts to move an order down the line
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto eachActiveLine) {
                eachActiveLine->attemptToMoveOrder();
            });
    
    if(m_cntCustomerOrder == (g_completed.size() + g_incomplete.size())){
        result = true;
    }
    return result;
}


void LineManager::display(std::ostream& os) const{
    for(size_t i = 0; i < m_activeLine.size(); i++)
        m_activeLine[i]->display(os);
}

}//sdds


