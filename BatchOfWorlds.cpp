#include <iostream> 
#include "World.hpp"
#include "BatchOfWorlds.hpp"


using namespace std;


BatchOfWorlds::BatchOfWorlds()
{
    cout << "Initializing a new batch of simulation:" << endl;
    cout << "Total number of simulation (int):" << endl;
    cin >> m_nSim;
    /*    cout << "Creation of a M x N World of Cell ..." << endl;
    cout << "Value of M (int):" << endl;
    cin >> m_WorldsHeight;
    cout << "Value of N (int):" << endl;
    cin >> m_WorldsWidth;*/
    cout << "Maximum number of iterations:" << endl;
    cin >> m_maxStep;
}

void BatchOfWorlds::Simulate()
{

    int nStep = 0;
    bool worldAlive = true;
    World myWorld;

    myWorld.createNeighbourhood();

    while (nStep < m_maxStep && worldAlive )
    {
        cout << "World: " << m_batchId << ", time step: " << nStep << endl;
        myWorld.nextStep();
        myWorld.printWorld();
        cout << "----" << endl;
        myWorld.printWorldFile();
        worldAlive = myWorld.isAlive();
        nStep++;
    }

    m_batchId++;
}


void BatchOfWorlds::SimulateAll(BatchOfWorlds myBatch)
{
    for (int iSim = 0 ; iSim < myBatch.m_nSim ; iSim++)
    {
        myBatch.Simulate();
    }
}