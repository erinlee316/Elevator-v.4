// Programmer: Erin Lee
// Student id: 1805820
// File: Building.h

#ifndef BUILDING_H
#define BUILDING_H

#include "Floor.h"
#include "Elevator.h"

// struct variable for building
struct Building
{
  static Floor floors[];
  static Elevator elevators[];
  static const int FLOORS;
  static const int ELEVATORS;

  // helper functions
  static void getDifferentInts(int&, int&);
  static int getPoisson(double);
  static void placeNewRiders(double);

  // actions
  static void action(double); // the main "action function"
  static bool openDoorToDisembarkRider(int); // step 1 of 9
  static bool disembarkRider(int); // parameter is an elevator's index
  static bool boardRider(int); // parameter is an elevator's index
  static bool waitingForMoreRiders(int);
  static bool doneWaitingMove(int);
  static bool moveableMove(int);
  static bool setIdleElevatorInMotion(int);
  static bool sendIdleElevatorToCallingFloor(int);
};
#endif
