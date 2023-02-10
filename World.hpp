#ifndef DEF_WORLD
#define DEF_WORLD
#include <iostream> 
#include "Cell.hpp"
#include <vector>
#include <map>
#include <fstream>

class World
{
    public:

    World();
    ~World();
    void printWorld();
    void printWorldFile();
    void createNeighbourhood();
    void nextStep();
    bool isAlive();

    protected:
    int m_step;
    static int m_id;
    constexpr static int WIDTH = 160; // note for myself ... if I want to use this variable to initialize an atribut, it needs to be static and const.
    constexpr static int HEIGHT = 80;
    std::map<int,Cell*> m_cellArray;
    int m_neighbourhingTable[WIDTH+2][HEIGHT+2];
};


#endif // WORLD