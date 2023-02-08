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
    int m_step;
    constexpr static int WIDTH = 6; // note for myself ... if I want to use this variable to initialize an atribut, it needs to be static and const.
    constexpr static int HEIGHT = 6;
    
    std::map<int,Cell*> m_cellArray;
    int m_neighbourhingTable[WIDTH+2][HEIGHT+2];
};


#endif // WORLD