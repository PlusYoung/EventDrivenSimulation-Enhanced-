#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
        const string &paramFname
) {
    bool success = true;;
    ifstream paramF;

    paramF.open(paramFname.c_str());

    //Check that the file was able to be opened...
    if (paramF.fail()) {
        success = false;
        cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
    } else {
        //Now read in all the params, according to the specified format of
        //the text-based parameter file.
        if (success) {
            paramF >> randomSeedVal;
            if (paramF.fail() ||
                randomSeedVal < 0) {
                success = false;
                cout << "ERROR: Unable to read/set random generatsor seed"
                     << endl;
            }
        }

        if (success) {
            paramF >> timeToStopSim;
            if (paramF.fail() ||
                timeToStopSim <= 0) {
                success = false;
                cout << "ERROR: Unable to read/set simulation end time" << endl;
            }
        }

        if (success) {
            paramF >> eastWestGreenTime >> eastWestYellowTime;
            if (paramF.fail() ||
                eastWestGreenTime <= 0 ||
                eastWestYellowTime <= 0) {
                success = false;
                cout << "ERROR: Unable to read/set east-west times" << endl;
            }
        }

        if (success) {
            paramF >> northSouthGreenTime >> northSouthYellowTime;
            if (paramF.fail() ||
                northSouthGreenTime <= 0 ||
                northSouthYellowTime <= 0) {
                success = false;
                cout << "ERROR: Unable to read/set north-south times" << endl;
            }
        }

        if (success) {
            paramF >> eastArrivalMean >> eastArrivalStdDev;
            if (paramF.fail() ||
                eastArrivalMean <= 0 ||
                eastArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set east arrival distribution"
                     << endl;
            }
        }

        if (success) {
            paramF >> westArrivalMean >> westArrivalStdDev;
            if (paramF.fail() ||
                westArrivalMean <= 0 ||
                westArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set west arrival distribution"
                     << endl;
            }
        }

        if (success) {
            paramF >> northArrivalMean >> northArrivalStdDev;
            if (paramF.fail() ||
                northArrivalMean <= 0 ||
                northArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set north arrival distribution"
                     << endl;
            }
        }

        if (success) {
            paramF >> southArrivalMean >> southArrivalStdDev;
            if (paramF.fail() ||
                southArrivalMean <= 0 ||
                southArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set south arrival distribution"
                     << endl;
            }
        }

        if (success) {
            paramF >> percentCarsAdvanceOnYellow;
            if (paramF.fail() ||
                percentCarsAdvanceOnYellow < 0 ||
                percentCarsAdvanceOnYellow > 100) {
                success = false;
                cout << "ERROR: Unable to read/set percentage yellow advance"
                     << endl;
            }

            //Use the specified seed to seed the random number generator
            setSeed(randomSeedVal);
        }

        paramF.close();
    }

    //Let the caller know whether things went well or not by printing the
    if (!success) {
        cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
             "simulation is NOT setup properly!" << endl;
        isSetupProperly = false;
    } else {
        cout << "Parameters read in successfully - simulation is ready!"
             << endl;
        isSetupProperly = true;
    }
}

void IntersectionSimulationClass::printParameters() const {
    cout << "===== Begin Simulation Parameters =====" << endl;
    if (!isSetupProperly) {
        cout << "  Simulation is not yet properly setup!" << endl;
    } else {
        cout << "  Random generator seed: " << randomSeedVal << endl;
        cout << "  Simulation end time: " << timeToStopSim << endl;

        cout << "  East-West Timing -" <<
             " Green: " << eastWestGreenTime <<
             " Yellow: " << eastWestYellowTime <<
             " Red: " << getEastWestRedTime() << endl;

        cout << "  North-South Timing -" <<
             " Green: " << northSouthGreenTime <<
             " Yellow: " << northSouthYellowTime <<
             " Red: " << getNorthSouthRedTime() << endl;

        cout << "  Arrival Distributions:" << endl;
        cout << "    East - Mean: " << eastArrivalMean <<
             " StdDev: " << eastArrivalStdDev << endl;
        cout << "    West - Mean: " << westArrivalMean <<
             " StdDev: " << westArrivalStdDev << endl;
        cout << "    North - Mean: " << northArrivalMean <<
             " StdDev: " << northArrivalStdDev << endl;
        cout << "    South - Mean: " << southArrivalMean <<
             " StdDev: " << southArrivalStdDev << endl;

        cout << "  Percentage cars advancing through yellow: " <<
             percentCarsAdvanceOnYellow << endl;
    }
    cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
        const string &travelDir
) {
    //represent the new arrival event to store the direction and time
    EventClass newArrivalEvent;
    //it's the time car spends on arriving queue
    int spendTime;
    //it's the time car arrives
    int arriveTime;

    if (travelDir == EAST_DIRECTION) {
        spendTime = getPositiveNormal(eastArrivalMean,
                                      eastArrivalStdDev);
        arriveTime = spendTime + currentTime;
        newArrivalEvent = EventClass(arriveTime,
                                     EVENT_ARRIVE_EAST);
    } else if (travelDir == WEST_DIRECTION) {
        spendTime = getPositiveNormal(westArrivalMean,
                                      westArrivalStdDev);
        arriveTime = spendTime + currentTime;
        newArrivalEvent = EventClass(arriveTime,
                                     EVENT_ARRIVE_WEST);
    } else if (travelDir == NORTH_DIRECTION) {
        spendTime = getPositiveNormal(northArrivalMean,
                                      northArrivalStdDev);
        arriveTime = spendTime + currentTime;
        newArrivalEvent = EventClass(arriveTime,
                                     EVENT_ARRIVE_NORTH);
    } else if (travelDir == SOUTH_DIRECTION) {
        spendTime = getPositiveNormal(southArrivalMean,
                                      southArrivalStdDev);
        arriveTime = spendTime + currentTime;
        newArrivalEvent = EventClass(arriveTime,
                                     EVENT_ARRIVE_SOUTH);
    }

    eventList.insertValue(newArrivalEvent);
    cout << "Time: " << currentTime
         << " Scheduled " << newArrivalEvent << endl;
}

void IntersectionSimulationClass::scheduleLightChange(
) {
    //represent the light change event
    EventClass lightChange;

    cout << "Time: " << currentTime << " Scheduled ";
    if (currentLight == LIGHT_GREEN_EW) {
        currentTime += eastWestGreenTime;
        lightChange = EventClass(currentTime,
                                 EVENT_CHANGE_YELLOW_EW);
    } else if (currentLight == LIGHT_YELLOW_EW) {
        currentTime += eastWestYellowTime;
        lightChange = EventClass(currentTime,
                                 EVENT_CHANGE_GREEN_NS);
    } else if (currentLight == LIGHT_GREEN_NS) {
        currentTime += northSouthGreenTime;
        lightChange = EventClass(currentTime,
                                 EVENT_CHANGE_YELLOW_NS);
    } else if (currentLight == LIGHT_YELLOW_NS) {
        currentTime += northSouthYellowTime;
        lightChange = EventClass(currentTime,
                                 EVENT_CHANGE_GREEN_EW);
    }
    eventList.insertValue(lightChange);
    cout << lightChange << endl;
}

bool IntersectionSimulationClass::handleNextEvent(
) {
    //represent the event to be handled.
    EventClass nextEvent;
    cout << endl;
    //condition 1: event list is empty
    if (eventList.getNumElems() == 0) {
        cout << "There is no event to be handled" << endl;
        return false;
    }
    eventList.removeFront(nextEvent);
    currentTime = nextEvent.getTimeOccurs();
    //condition 2: simulation time is out of bound
    if (currentTime > timeToStopSim) {
        cout << "Next event occurs AFTER the simulation end time ("
             << nextEvent << ")!" << endl;
        return false;
    }

    cout << "Handling " << nextEvent << endl;
    //condition 3: simulate 8 events normally
    if (nextEvent.getType() == EVENT_ARRIVE_EAST) {
        CarClass carEast(EAST_DIRECTION, currentTime);
        eastQueue.enqueue(carEast);
        if (eastQueue.getNumElems() > maxEastQueueLength) {
            maxEastQueueLength = eastQueue.getNumElems();
        }
        cout << "Time: " << currentTime << " Car #"
             << carEast.getId()
             << " arrives east-bound - queue length: "
             << eastQueue.getNumElems() << endl;
        scheduleArrival(EAST_DIRECTION);
    } else if (nextEvent.getType() == EVENT_ARRIVE_WEST) {

        CarClass carWest(WEST_DIRECTION, currentTime);
        westQueue.enqueue(carWest);
        if (westQueue.getNumElems() > maxWestQueueLength) {
            maxWestQueueLength = westQueue.getNumElems();
        }
        cout << "Time: " << currentTime << " Car #"
             << carWest.getId()
             << " arrives west-bound - queue length: "
             << westQueue.getNumElems() << endl;

        scheduleArrival(WEST_DIRECTION);
    } else if (nextEvent.getType() == EVENT_ARRIVE_NORTH) {

        CarClass carNorth(NORTH_DIRECTION, currentTime);
        northQueue.enqueue(carNorth);
        if (northQueue.getNumElems() > maxNorthQueueLength) {
            maxNorthQueueLength = northQueue.getNumElems();
        }
        cout << "Time: " << currentTime << " Car #"
             << carNorth.getId()
             << " arrives north-bound - queue length: "
             << northQueue.getNumElems() << endl;

        scheduleArrival(NORTH_DIRECTION);
    } else if (nextEvent.getType() == EVENT_ARRIVE_SOUTH) {

        CarClass carSouth(SOUTH_DIRECTION, currentTime);
        southQueue.enqueue(carSouth);
        if (southQueue.getNumElems() > maxSouthQueueLength) {
            maxSouthQueueLength = southQueue.getNumElems();
        }
        cout << "Time: " << currentTime << " Car #"
             << carSouth.getId()
             << " arrives south-bound - queue length: "
             << southQueue.getNumElems() << endl;

        scheduleArrival(SOUTH_DIRECTION);
    } else if (nextEvent.getType() == EVENT_CHANGE_GREEN_EW) {
        cout << "Advancing cars on north-south yellow" << endl;

        //represent the car to go
        CarClass carNorthSouth;
        //represent the number of cars advance in each direction
        int northCount = 0;
        int southCount = 0;

        //represent if the car stop or there is no car
        bool ifStop = false;
        //while loop to simulate car advance
        while (!ifStop &&
               northCount < northSouthYellowTime) {
            //check if there is car in queue
            if (northQueue.getNumElems() == 0) {
                cout << "  No north-bound cars waiting to advance on yellow"
                     << endl;
                ifStop = true;
            } else {
                //car advances in north
                if (getUniform(1, 100) <= percentCarsAdvanceOnYellow) {
                    northQueue.dequeue(carNorthSouth);
                    northCount++;
                    cout << "  Next north-bound car will advance on yellow"
                         << endl;
                    cout << "  Car #" << carNorthSouth.getId()
                         << " advances north-bound" << endl;
                }
                    //the car stops
                else {
                    ifStop = true;
                    cout << "  Next north-bound car will NOT advance on yellow"
                         << endl;
                }
            }
        }
        //reset the ifStop to false
        ifStop = false;
        while (!ifStop &&
               southCount < northSouthYellowTime) {
            //check if there is car in queue
            if (southQueue.getNumElems() == 0) {
                cout << "  No south-bound cars waiting to advance on yellow"
                     << endl;
                ifStop = true;
            } else {
                //car advances in south
                if (getUniform(1, 100) <= percentCarsAdvanceOnYellow) {
                    southQueue.dequeue(carNorthSouth);
                    southCount++;
                    cout << "  Next south-bound car will advance on yellow"
                         << endl;
                    cout << "  Car #" << carNorthSouth.getId()
                         << " advances south-bound" << endl;
                }
                    //the car stops
                else {
                    ifStop = true;
                    cout << "  Next south-bound car will NOT advance on yellow";
                    cout << endl;
                }
            }
        }

        cout << "North-bound cars advanced on yellow: "
             << northCount << " Remaining queue: "
             << northQueue.getNumElems() << endl;
        cout << "South-bound cars advanced on yellow: "
             << southCount << " Remaining queue: "
             << southQueue.getNumElems() << endl;

        //change the light
        currentLight = LIGHT_GREEN_EW;
        scheduleLightChange();
        numTotalAdvancedNorth += northCount;
        numTotalAdvancedSouth += southCount;
    } else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_EW) {
        cout << "Advancing cars on east-west green" << endl;

        //represent the car to go
        CarClass carEastWest;
        //represent the number of cars advance in each direction
        int eastCount = 0;
        int westCount = 0;
        //condition 1: car advances in east
        while (eastQueue.getNumElems() > 0 &&
               eastCount < eastWestGreenTime) {
            eastQueue.dequeue(carEastWest);
            eastCount++;
            cout << "  Car #" << carEastWest.getId()
                 << " advances east-bound" << endl;
        }
        //condition 2: car advances in west
        while (westQueue.getNumElems() > 0 &&
               westCount < eastWestGreenTime) {
            //the car advances
            westQueue.dequeue(carEastWest);
            westCount++;
            cout << "  Car #" << carEastWest.getId()
                 << " advances west-bound" << endl;
        }

        cout << "East-bound cars advanced on green: "
             << eastCount << " Remaining queue: "
             << eastQueue.getNumElems() << endl;
        cout << "West-bound cars advanced on green: "
             << westCount << " Remaining queue: "
             << westQueue.getNumElems() << endl;

        //change the light
        currentLight = LIGHT_YELLOW_EW;
        scheduleLightChange();
        numTotalAdvancedEast += eastCount;
        numTotalAdvancedWest += westCount;
    } else if (nextEvent.getType() == EVENT_CHANGE_GREEN_NS) {
        cout << "Advancing cars on east-west yellow" << endl;

        //represent the car to go
        CarClass carEastWest;
        //represent the number of cars advance in each direction
        int eastCount = 0;
        int westCount = 0;

        //represent if the car stop or there is no car
        bool ifStop = false;
        //while loop to simulate car advance
        while (!ifStop &&
               eastCount < northSouthYellowTime) {
            //check if there is car in queue
            if (eastQueue.getNumElems() == 0) {
                cout << "  No east-bound cars waiting to advance on yellow"
                     << endl;
                ifStop = true;
            } else {
                //car advances in north
                if (getUniform(1, 100) <= percentCarsAdvanceOnYellow) {
                    eastQueue.dequeue(carEastWest);
                    eastCount++;
                    cout << "  Next east-bound car will advance on yellow"
                         << endl;
                    cout << "  Car #" << carEastWest.getId()
                         << " advances east-bound" << endl;
                }
                    // the car stops
                else {
                    ifStop = true;
                    cout << "  Next east-bound car will NOT advance on yellow"
                         << endl;
                }
            }
        }
        //reset the ifStop to false
        ifStop = false;
        while (!ifStop &&
               westCount < eastWestYellowTime) {
            //check if there is car in queue
            if (westQueue.getNumElems() == 0) {
                cout << "  No west-bound cars waiting to advance on yellow"
                     << endl;
                ifStop = true;
            } else {
                //car advances in west
                if (getUniform(1, 100) <= percentCarsAdvanceOnYellow) {
                    westQueue.dequeue(carEastWest);
                    westCount++;
                    cout << "  Next west-bound car will advance on yellow"
                         << endl;
                    cout << "  Car #" << carEastWest.getId()
                         << " advances west-bound" << endl;
                }
                    // the car stops
                else {
                    ifStop = true;
                    cout << "  Next west-bound car will NOT advance on yellow"
                         << endl;
                }
            }
        }

        cout << "East-bound cars advanced on yellow: "
             << eastCount << " Remaining queue: "
             << eastQueue.getNumElems() << endl;
        cout << "West-bound cars advanced on yellow: "
             << westCount << " Remaining queue: "
             << westQueue.getNumElems() << endl;

        //change the light
        currentLight = LIGHT_GREEN_NS;
        scheduleLightChange();
        numTotalAdvancedEast += eastCount;
        numTotalAdvancedWest += westCount;
    } else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_NS) {
        cout << "Advancing cars on north-south green" << endl;

        //represent the car to go
        CarClass carNorthSouth;
        //represent the number of cars advance in each direction
        int northCount = 0;
        int southCount = 0;

        //condition 3: car advances in north
        while (northQueue.getNumElems() > 0 &&
               northCount < northSouthGreenTime) {
            northQueue.dequeue(carNorthSouth);
            northCount++;
            cout << "  Car #" << carNorthSouth.getId()
                 << " advances north-bound" << endl;
        }
        //condition 4: car advances in south
        while (southQueue.getNumElems() > 0 &&
               southCount < northSouthGreenTime) {
            //the car advances
            southQueue.dequeue(carNorthSouth);
            southCount++;
            cout << "  Car #" << carNorthSouth.getId()
                 << " advances south-bound" << endl;
        }

        cout << "North-bound cars advanced on green: "
             << northCount << " Remaining queue: "
             << northQueue.getNumElems() << endl;
        cout << "South-bound cars advanced on green: "
             << southCount << " Remaining queue: "
             << southQueue.getNumElems() << endl;

        //change the light
        currentLight = LIGHT_YELLOW_NS;
        scheduleLightChange();
        numTotalAdvancedNorth += northCount;
        numTotalAdvancedSouth += southCount;
    }

    return true;
}

void IntersectionSimulationClass::printStatistics(
) const {
    cout << "===== Begin Simulation Statistics =====" << endl;
    cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
    cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
    cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
    cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
    cout << "  Total cars advanced east-bound: " <<
         numTotalAdvancedEast << endl;
    cout << "  Total cars advanced west-bound: " <<
         numTotalAdvancedWest << endl;
    cout << "  Total cars advanced north-bound: " <<
         numTotalAdvancedNorth << endl;
    cout << "  Total cars advanced south-bound: " <<
         numTotalAdvancedSouth << endl;
    cout << "===== End Simulation Statistics =====" << endl;
}
