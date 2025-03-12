//
// Created by 32874 on 2025/3/4.
//

#ifndef GRAPHCPRO_TOURISM_H
#define GRAPHCPRO_TOURISM_H

#include "Graph.h"

class CTourism{
private:
    CGraph m_cGraph;
public:
    CTourism(void){

    }
    ~CTourism(void){

    }
    void CreateGraph(void);
    void GetSpotInfo(void);
    void TravelPath(void);
    void FindShortPath(void);
    void DesignPath(void);
};



#endif //GRAPHCPRO_TOURISM_H
