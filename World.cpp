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

    for (int i=1;i<dimX+1;i++)
    {
        neighbourhingTable[i][0] = neighbourhingTable[i][dimY];
        neighbourhingTable[i][dimY+1] = neighbourhingTable[i][1];
    }
    for (int j=1;j<dimY+1;j++)
    {
        neighbourhingTable[0][j] = neighbourhingTable[dimX][j];
        neighbourhingTable[dimX+1][j] = neighbourhingTable[1][j];
    }

    neighbourhingTable[0][0] = neighbourhingTable[dimX][dimY];
    neighbourhingTable[dimX+1][0] = neighbourhingTable[1][dimY];
    neighbourhingTable[dimX+1][dimY+1] = neighbourhingTable[1][1];
    neighbourhingTable[0][dimY+1] = neighbourhingTable[dimX][1];


    cout << endl;
}

World::~World()
{
    for (int iter=0; iter<dimX*dimY; iter++)
    {
        delete currentState[iter];
        currentState[iter] = nullptr;
    }
}

void World::createNeighbourhood()
{
    /* instead of computing the indices by hand here, we'll use the neighbouring table ...*/

    vector<Cell*> neighbours;
    int neighbourList[8];
    int inbtl, inbtm, inbtr, inbbl, inbbm, inbbr, inbml, inbmr;
    int nbrsId[8];

    int iter=0;
    for (int i=1;i<dimX+1;i++)
    {
        for (int j=1;j<dimY+1;j++)
        {
            neighbourList[0] = neighbourhingTable[i-1][j-1];
            neighbourList[1] = neighbourhingTable[i-1][j];
            neighbourList[2] = neighbourhingTable[i-1][j+1];
            neighbourList[3] = neighbourhingTable[i][j-1];
            neighbourList[4] = neighbourhingTable[i][j+1];
            neighbourList[5] = neighbourhingTable[i+1][j-1];
            neighbourList[6] = neighbourhingTable[i+1][j];
            neighbourList[7] = neighbourhingTable[i+1][j+1];

            for (int icell = 0; icell<8; icell++)
            {
                neighbours.push_back(currentState[neighbourList[icell]]); // fill the vector with the correct Cell pointers
            }

            currentState[iter]->assignNeighbours(neighbours); // give the vector of Cell pointers to the Cell

            for (int icell = 0; icell<8; icell++)
            {
                neighbours.pop_back(); //clear the vector ...
            }
            iter++;
        }
    }

    for (int iter= 0; iter < dimX*dimY; iter++)
    {

    }

}

void World::advance()
{
    for (int iter=0; iter<dimX*dimY; iter++)
    {
            currentState[iter]->sendStatus();
    }

    /* ça ne peut pas fonctionner car je ne recopie pas le tableau d'un pas à l'autre ...*/
    /* faire une copie toute bête demande de recalculer les relations de voisinages ...*/
    for (int iter=0; iter<dimX*dimY; iter++)
    {
            currentState[iter]->stepForward();
    }

    /* du coup c'est assez sous optimal, comme il faut que je parcours deux fois le tableau ...*/
    for (int iter=0; iter<dimX*dimY; iter++)
    {
        currentState[iter]->update();
    }
}


void World::printWorld()
{
    for (int iter=0; iter<dimX*dimY; iter++)
    {
        currentState[iter]->printFlux(cout);

        if ((iter+1)%dimX==0)
        {
            cout << endl;
        }
    }
}
