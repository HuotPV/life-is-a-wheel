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
        currentState[iCell] = new Cell(); // put new Cell pointer in currentState
    }

    /* also create the neighbouring table*/
    int iter=0;
    for (int iLine=1 ; iLine<HEIGHT+1 ; iLine++)
    {
        for (int iCol=1 ; iCol<WIDTH+1 ; iCol++)
        {
            neighbourhingTable[iLine][iCol]=iter++;
        }
    }

    for (int iLine=1 ; iLine<HEIGHT+1 ; iLine++)
    {
        neighbourhingTable[iLine][0] = neighbourhingTable[iLine][WIDTH];
        neighbourhingTable[iLine][WIDTH+1] = neighbourhingTable[iLine][1];
    }
    for (int iLine=1 ; iLine<WIDTH+1 ; iLine++)
    {
        neighbourhingTable[0][iLine] = neighbourhingTable[HEIGHT][iLine];
        neighbourhingTable[HEIGHT+1][iLine] = neighbourhingTable[1][iLine];
    }

    neighbourhingTable[0][0] = neighbourhingTable[HEIGHT][WIDTH];
    neighbourhingTable[HEIGHT+1][0] = neighbourhingTable[1][WIDTH];
    neighbourhingTable[HEIGHT+1][WIDTH+1] = neighbourhingTable[1][1];
    neighbourhingTable[0][WIDTH+1] = neighbourhingTable[HEIGHT][1];
}

World::~World()
{
    for (int iCell=0 ; iCell<HEIGHT*WIDTH ; iCell++)
    {
        delete currentState[iCell];
        currentState[iCell] = nullptr;
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
            neighbourList[0] = neighbourhingTable[iLine-1][iCol-1];
            neighbourList[1] = neighbourhingTable[iLine-1][iCol];
            neighbourList[2] = neighbourhingTable[iLine-1][iCol+1];
            neighbourList[3] = neighbourhingTable[iLine][iCol-1];
            neighbourList[4] = neighbourhingTable[iLine][iCol+1];
            neighbourList[5] = neighbourhingTable[iLine+1][iCol-1];
            neighbourList[6] = neighbourhingTable[iLine+1][iCol];
            neighbourList[7] = neighbourhingTable[iLine+1][iCol+1];

            for (int iNb = 0 ; iNb<8 ; iNb++)
            {
                neighbours.push_back(currentState[neighbourList[iNb]]); // fill the vector with the correct Cell pointers
            }

            currentState[iCell]->assignNeighbours(neighbours); // give the vector of Cell pointers to the Cell

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
        currentState[iCell]->stepForward();
    }

    /* du coup c'est assez sous optimal, comme il faut que je parcours deux fois le tableau ...*/
    for (int iCell=0 ; iCell < HEIGHT*WIDTH ; iCell++)
    {
        currentState[iCell]->update();
    }
}


void World::printWorld()
{
    for (int iCell=0 ; iCell < HEIGHT*WIDTH ; iCell++)
    {
        currentState[iCell]->printFlux(cout);

        if ((iCell+1)%WIDTH == 0)
        {
            cout << endl;
        }
    }
}
