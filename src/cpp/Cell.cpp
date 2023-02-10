#include "Cell.hpp"
#include <vector>
#include <fstream>
using namespace std;

int Cell::id = 0; // initialisation de l'attribut statique compteur.


Cell::Cell()
{
    id++;
    isAlive = rand() % 2;
}
Cell::~Cell(){--id;} // on décrémente compteur à chaque destruction d'une instance

int Cell::sendStatus() const
{
    return isAlive;
}

void Cell::assignNeighbours(vector<Cell*> cells)
{
    for (int iCell = 0; iCell < 8; iCell++)
    {
        neighbours[iCell] = cells[iCell];
    }
} // version with vector of Cell*

void Cell::update()
{
    /* Replace the isAlive status by the willBeAlive one*/
    isAlive = willBeAlive;
}

void Cell::stepForward()
{
    int statusNeighbours = 0;

    for (int iNb = 0; iNb < 8; iNb++)
    {
        statusNeighbours += neighbours[iNb]->sendStatus();
    }

    if (isAlive)
    {
        if (statusNeighbours == 2 || statusNeighbours == 3)
        {   
            willBeAlive = 1;
        }
        else
        {
            willBeAlive = 0;
        }

    }
    else
    {
        if (statusNeighbours == 3)
        {
            willBeAlive = 1;
        }
        else
        {
            willBeAlive = 0;
        }
    }
}


ostream &operator<<( ostream &flux, Cell const& cell)
{
    cell.printFlux(flux);
    return flux;
}
void Cell::printFlux(ostream &flux) const
{
    flux << isAlive;
}
void Cell::printOfstream(ofstream &flux) const
{
    flux << isAlive << ' ';
}
