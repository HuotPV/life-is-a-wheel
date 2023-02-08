#include "World.hpp"
#include "Cell.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

World::World() : step(0)
{
    /* function that fills in the table */
    for (int iCell=0 ; iCell < HEIGHT*WIDTH ; iCell++)
    {
        m_cellArray[iCell] = new Cell(); // put new Cell pointer in cellArraye
    }

    /* also create the neighbouring table*/
    int iter=0;
    for (int iLine=1 ; iLine<HEIGHT+1 ; iLine++)
    {
        for (int iCol=1 ; iCol<WIDTH+1 ; iCol++)
        {
            m_neighbourhingTable[iLine][iCol]=iter++;
        }
    }

    for (int iLine=1 ; iLine<HEIGHT+1 ; iLine++)
    {
        m_neighbourhingTable[iLine][0] = m_neighbourhingTable[iLine][WIDTH];
        m_neighbourhingTable[iLine][WIDTH+1] = m_neighbourhingTable[iLine][1];
    }
    for (int iLine=1 ; iLine<WIDTH+1 ; iLine++)
    {
        m_neighbourhingTable[0][iLine] = m_neighbourhingTable[HEIGHT][iLine];
        m_neighbourhingTable[HEIGHT+1][iLine] = m_neighbourhingTable[1][iLine];
    }

    m_neighbourhingTable[0][0] = m_neighbourhingTable[HEIGHT][WIDTH];
    m_neighbourhingTable[HEIGHT+1][0] = m_neighbourhingTable[1][WIDTH];
    m_neighbourhingTable[HEIGHT+1][WIDTH+1] = m_neighbourhingTable[1][1];
    m_neighbourhingTable[0][WIDTH+1] = m_neighbourhingTable[HEIGHT][1];
}

World::~World()
{
    for (int iCell=0 ; iCell<HEIGHT*WIDTH ; iCell++)
    {
        delete m_cellArray[iCell];
        m_cellArray[iCell] = nullptr;
    }
}

void World::createNeighbourhood()
{
    /* instead of computing the indices by hand here, we'll use the neighbouring table ...*/

    vector<Cell*> neighbours;
    int neighbourList[8];
    int inbtl, inbtm, inbtr, inbbl, inbbm, inbbr, inbml, inbmr;
    int nbrsId[8];

    int iCell=0;
    for (int iLine=1 ;iLine<HEIGHT+1 ; iLine++)
    {
        for (int iCol=1 ; iCol<WIDTH+1 ; iCol++)
        {
            neighbourList[0] = m_neighbourhingTable[iLine-1][iCol-1];
            neighbourList[1] = m_neighbourhingTable[iLine-1][iCol];
            neighbourList[2] = m_neighbourhingTable[iLine-1][iCol+1];
            neighbourList[3] = m_neighbourhingTable[iLine][iCol-1];
            neighbourList[4] = m_neighbourhingTable[iLine][iCol+1];
            neighbourList[5] = m_neighbourhingTable[iLine+1][iCol-1];
            neighbourList[6] = m_neighbourhingTable[iLine+1][iCol];
            neighbourList[7] = m_neighbourhingTable[iLine+1][iCol+1];

            for (int iNb = 0 ; iNb<8 ; iNb++)
            {
                neighbours.push_back(m_cellArray[neighbourList[iNb]]); // fill the vector with the correct Cell pointers
            }

            m_cellArray[iCell]->assignNeighbours(neighbours); // give the vector of Cell pointers to the Cell

            for (int iNb = 0 ; iNb<8 ; iNb++)
            {
                neighbours.pop_back(); //clear the vector ...
            }
            iCell++;
        }
    }
}

void World::nextStep()
{
    /* ça ne peut pas fonctionner car je ne recopie pas le tableau d'un pas à l'autre ...*/
    /* faire une copie toute bête demande de recalculer les relations de voisinages ...*/
    for (int iCell=0 ; iCell < HEIGHT*WIDTH ; iCell++)
    {
        m_cellArray[iCell]->stepForward();
    }

    /* du coup c'est assez sous optimal, comme il faut que je parcours deux fois le tableau ...*/
    for (int iCell=0 ; iCell < HEIGHT*WIDTH ; iCell++)
    {
        m_cellArray[iCell]->update();
    }
}


void World::printWorld()
{
    for (int iCell=0 ; iCell < HEIGHT*WIDTH ; iCell++)
    {
        m_cellArray[iCell]->printFlux(cout);

        if ((iCell+1)%WIDTH == 0)
        {
            cout << endl;
        }
    }
}
