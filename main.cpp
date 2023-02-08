#include <iostream>
#include <cstdlib>
#include <ctime>
#include "World.hpp"
#include "Cell.hpp"
#include <string>
using namespace std;


int main()
{
    srand(time(0));

    World myWorld;
    cout << "myWorld successfully initialized ! " << endl;

    myWorld.createNeighbourhood();
    cout << "Neighbourhood created !" << endl;
    cout << "End of initialization." << endl;
    cout << endl;

    cout << "Initial state: " << endl;
    myWorld.printWorld();
    cout << endl;

    cout << "Run !" << endl;

    for (int tStep=0; tStep<4; tStep++)
    {
        cout << "Time step: " << tStep << endl;
        myWorld.nextStep();
        myWorld.printWorld();
        cout << "----" << endl;
        myWorld.printWorldFile();
    }

    cout << "End of run !" << endl;
}