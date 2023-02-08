#include "Cell.hpp"
#include <vector>

using namespace std;

int Cell::id = 0; // initialisation de l'attribut statique compteur.


Cell::Cell()
{
    id++;
    isAlive = rand() % 2;
}
Cell::~Cell(){--id;} // on décrémente compteur à chaque destruction d'une instance

void Cell::die()
{
    isAlive = 0;
}

void Cell::birth()
{
    isAlive = 1;
}

int Cell::sendStatus() const
{
    return isAlive;
}

/*void Cell::assignNeighbours(Cell* cells[8])
{
    for (int icell = 0; icell < 8; icell++)
    {
        neighbours[icell] = cells[icell];
    }
}*/ // version with table of Cell*

void Cell::assignNeighbours(vector<Cell*> cells)
{
    for (int icell = 0; icell < 8; icell++)
    {
        neighbours[icell] = cells[icell];
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

    for (int inb = 0; inb < 8; inb++)
    {
        statusNeighbours += neighbours[inb]->sendStatus();
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