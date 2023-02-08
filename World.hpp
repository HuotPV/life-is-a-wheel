#ifndef DEF_WORLD
#define DEF_WORLD
#include <iostream> 
#include "Cell.hpp"
#include <vector>
#include <map>

class World
{
    public:

    World();
    ~World();
    void printWorld();
    void createNeighbourhood();
    void advance();

    //void stepForward();


    protected:
    int step;
    constexpr static int dimX = 6; // note for myself ... if I want to use this variable to initialize the table currentState, it needs to be static and const.
    constexpr static int dimY = 6;
    //Cell* currentState[dimX][dimY] ;
    //std::vector<std::vector<Cell*>> currentState; 
    
    std::map<int,Cell*> currentState;
    int neighbourhingTable[dimX+2][dimY+2];
};


#endif // WORLD