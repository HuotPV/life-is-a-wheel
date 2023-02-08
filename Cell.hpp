#ifndef DEF_CELL
#define DEF_CELL
#include <iostream> 
#include <vector>



class Cell
{
    public:
    Cell();
    ~Cell();
    void die();
    void birth();
    void printFlux(std::ostream &flux) const;
    
    void assignNeighbours(std::vector<Cell*> cells);
    int sendStatus() const;
    int sumNeighbours() const;
    void stepForward();
    void update();

    protected:
    static int id;
    bool isAlive; // better than int status
    bool willBeAlive;
    Cell* neighbours[8];
};

std::ostream& operator<<(std::ostream &flux, Cell const& cell);


#endif // CELL