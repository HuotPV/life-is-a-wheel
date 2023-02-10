#ifndef DEF_BATCHOFWORLDS
#define DEF_BATCHOFWORLDS
#include <iostream> 
#include "Cell.hpp"
#include <vector>
#include <map>
#include <fstream>


class BatchOfWorlds
{
    public:

    BatchOfWorlds();
    void Simulate();
    void SimulateAll(BatchOfWorlds myBatch);

    protected:
    int m_WorldsHeight, m_WorldsWidth;
    int m_maxStep, m_nSim;
    int m_batchId;
};

#endif // BATCHOFWORLDS