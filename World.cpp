#include "World.hpp"
#include "Cell.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

World::World() : step(0)
{
    /* function that fills in the table */
    for (int iCell=0 ; iCell < dimX*dimY ; iCell++)
    {
        currentState[iCell] = new Cell(); // put new Cell pointer in currentState
    }

    /* also create the neighbouring table*/
    int iter=0;
    for (int iLine=1;iLine<dimX+1;iLine++)
    {
        for (int iCol=1;iCol<dimY+1;iCol++)
        {
            neighbourhingTable[iLine][iCol]=iter++;
        }
    }

    for (int iLine=1;iLine<dimX+1;iLine++)
    {
        neighbourhingTable[iLine][0] = neighbourhingTable[iLine][dimY];
        neighbourhingTable[iLine][dimY+1] = neighbourhingTable[iLine][1];
    }
    for (int iLine=1;iLine<dimY+1;iLine++)
    {
        neighbourhingTable[0][iLine] = neighbourhingTable[dimX][iLine];
        neighbourhingTable[dimX+1][iLine] = neighbourhingTable[1][iLine];
    }

    neighbourhingTable[0][0] = neighbourhingTable[dimX][dimY];
    neighbourhingTable[dimX+1][0] = neighbourhingTable[1][dimY];
    neighbourhingTable[dimX+1][dimY+1] = neighbourhingTable[1][1];
    neighbourhingTable[0][dimY+1] = neighbourhingTable[dimX][1];


    cout << endl;
}

World::~World()
{
    for (int iCell=0; iCell<dimX*dimY; iCell++)
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
    for (int iLine=1;iLine<dimX+1;iLine++)
    {
        for (int iCol=1;iCol<dimY+1;iCol++)
        {
            neighbourList[0] = neighbourhingTable[iLine-1][iCol-1];
            neighbourList[1] = neighbourhingTable[iLine-1][iCol];
            neighbourList[2] = neighbourhingTable[iLine-1][iCol+1];
            neighbourList[3] = neighbourhingTable[iLine][iCol-1];
            neighbourList[4] = neighbourhingTable[iLine][iCol+1];
            neighbourList[5] = neighbourhingTable[iLine+1][iCol-1];
            neighbourList[6] = neighbourhingTable[iLine+1][iCol];
            neighbourList[7] = neighbourhingTable[iLine+1][iCol+1];

            for (int iNb = 0; iNb<8; iNb++)
            {
                neighbours.push_back(currentState[neighbourList[iNb]]); // fill the vector with the correct Cell pointers
            }

            currentState[iCell]->assignNeighbours(neighbours); // give the vector of Cell pointers to the Cell

            for (int iNb = 0; iNb<8; iNb++)
            {
                neighbours.pop_back(); //clear the vector ...
            }
            iCell++;
        }
    }
}

void World::advance()
{
    /* ça ne peut pas fonctionner car je ne recopie pas le tableau d'un pas à l'autre ...*/
    /* faire une copie toute bête demande de recalculer les relations de voisinages ...*/
    for (int iCell=0; iCell<dimX*dimY; iCell++)
    {
            currentState[iCell]->stepForward();
    }

    /* du coup c'est assez sous optimal, comme il faut que je parcours deux fois le tableau ...*/
    for (int iCell=0; iCell<dimX*dimY; iCell++)
    {
        currentState[iCell]->update();
    }
}


void World::printWorld()
{
    for (int iCell=0; iCell<dimX*dimY; iCell++)
    {
        currentState[iCell]->printFlux(cout);

        if ((iCell+1)%dimX==0)
        {
            cout << endl;
        }
    }
}
