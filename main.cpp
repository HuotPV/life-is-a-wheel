#include <iostream>
#include <cstdlib>
#include <ctime>
#include "World.hpp"
#include "Cell.hpp"
#include "BatchOfWorlds.hpp"
#include <string>
using namespace std;


int main()
{
    srand(time(0));

    BatchOfWorlds myBatchOfWorlds;

    myBatchOfWorlds.SimulateAll(myBatchOfWorlds);

}