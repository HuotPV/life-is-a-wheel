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
    void nextStep();

    protected:
    int step;
    constexpr static int WIDTH = 6; // note for myself ... if I want to use this variable to initialize the table currentState, it needs to be static and const.
    constexpr static int HEIGHT = 6;
    
    std::map<int,Cell*> currentState;
    int neighbourhingTable[WIDTH+2][HEIGHT+2];
};


#endif // WORLD