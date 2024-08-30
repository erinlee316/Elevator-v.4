// Programmer: Erin Lee
// Student id: 1805820
// File: Building.cpp

#include "Building.h"
#include "Floor.h"
#include "Elevator.h"

#include <iostream>
using namespace std;

#include <cstdlib>
#include <cmath>

// 
Floor Building::floors[] = 
{
  Floor(0, "Basement", "B"),
  Floor(50, "Ground Floor", "G"),
  Floor(100, "Second Floor", "2"),
  Floor(150, "Third Floor", "3"),
  Floor(200, "Fourth Floor", "4"),
  Floor(250, "Roof Top", "5"),
};

const int Building::FLOORS = sizeof(floors) / sizeof(Floor);

Elevator Building::elevators[] =
{
  Elevator(10, 5, 0),
  Elevator(15, 10, 1),
  Elevator(20, 2, 2),
  Elevator(25, 25, 3),
};

const int Building::ELEVATORS = sizeof(elevators) / sizeof(Elevator);

// used by Building::placeNewRiders
void Building::getDifferentInts(int& a, int& b)
{
  do
  {
    a = rand() % FLOORS; // range is 0 to (FLOORS-1)
    b = rand() % FLOORS; // range is 0 to (FLOORS-1)
  } 
  
  while (a == b); // try again if they are the same
}

// used by Building::placeNewRiders
int Building::getPoisson(double avg)
{
  int arrivals = 0;
  double probOfnArrivals = exp(-avg); // requires cmath
  for(double randomValue = (rand() % 1000) / 1000.0; // requires cstdlib
    (randomValue -= probOfnArrivals) > 0.0;
    probOfnArrivals *= avg / ++arrivals);
  return arrivals;
}

// given an arrival rate, randomly select #of riders to add...
// ...and add them to randomly selected floors with random destinations
void Building::placeNewRiders(double arrivalsPerSecond)
{
  int n = getPoisson(arrivalsPerSecond);
  for (int i = 0; i < n; i++)
  {
    int from, to;
    getDifferentInts(from, to);
    Rider rider(from, to);
    floors[from].addRider(rider);
  }
}

// STEP 1 of 9, "Open their door if there is a rider to disembark"
bool Building::openDoorToDisembarkRider(int e)
{
  if (!elevators[e].isOpen()) // if the door is closed...
    for (int f = 0; f < FLOORS; f++) // check each floor to see if its elevation matches
      if (floors[f] == elevators[e] && elevators[e].panel.isLit(floors[f].label)) // ...and the elevator's panel has that floor lit
      {
        elevators[e].openDoorTo(f); // then open the door to that floor
        return true; // ...and report that an action was taken
      }
    
  return false; // if I get this far, no action was taken in this function
}

// the "action function" to perform one action per elevator per time step
void Building::action(double arrivalsPerSecond)
{
  placeNewRiders(arrivalsPerSecond);

  // one action per elevator
  for (int e = 0; e < ELEVATORS; e++)
  {
    if (openDoorToDisembarkRider(e)) continue; // step 1 of 9
    if (disembarkRider(e)) continue;
    if (boardRider(e)) continue;
    if (waitingForMoreRiders(e)) continue;
    if (doneWaitingMove(e)) continue;
    if (moveableMove(e)) continue;
    if (setIdleElevatorInMotion(e)) continue;
    if (sendIdleElevatorToCallingFloor(e)) continue;
    elevators[e].goIdle();
  }
}

// member function will let rider leave from elevator  
bool Building::disembarkRider(int e) // Assignment 9
{
  // if open and rider to disembark, do that
  if (elevators[e].isOpen() && elevators[e].hasRiderForFloor())
  {
    // remove rider from elevator
    // return true after rider is disembarked
    elevators[e].removeRider();
    return true;
  }

  // no rider to disembark
  return false;
}

// member function will let rider board onto elevator 
bool Building::boardRider(int e) // Assignment 9
{
  // check if door is open and not full and rider to load, load
  if (elevators[e].isOpen() && !elevators[e].isFull())
  {
    // get reference to floor where elevator is located currently
    Floor& floor = floors[elevators[e].getFloorIndex()];

    // check if elevator is going up and has up-riders on the floor
    if (elevators[e].goingUp() && floor.hasUpRider())
    {
      // remove rider from floor
      // board riders onto elevator
      Rider rider = floor.removeUpRider();
      elevators[e].board(rider);
      return true;
    }

    // check if elevator is going down and has down-riders on the floor
    else if (elevators[e].goingDown() && floor.hasDownRider())
    {
      // remove rider from floor
      // board riders onto elevator
      Rider rider = floor.removeDownRider();
      elevators[e].board(rider);
      return true;
    }
  }

  // return false if no riders to load OR door is not open OR elevator is full
  return false;
}

// member function will count down time starting from 3 seconds
bool Building::waitingForMoreRiders(int e)
{
  // check if elevator is open AND not idle AND has not yet reached 0 seconds
  if (elevators[e].isOpen() && !elevators[e].isIdle() && !elevators[e].timedOut())
  {
    elevators[e].tickTimer();
    return true;
  }

  // return false if conditions not met
  else
    return false;
}

// member function closes door and makes it move
bool Building::doneWaitingMove(int e)
{
  // check if elevator is open AND not idle AND has reached at 0 seconds
  // if yes, close door and move
  if (elevators[e].isOpen() && !elevators[e].isIdle() && elevators[e].timedOut())
  {
    elevators[e].closeDoor();
    elevators[e].move();
    return true;
  }

  // conditions are false, do not move
  else
    return false;
}

// member function moves elevator
bool Building::moveableMove(int e)
{
  // check if elevator is open or idle
  if (elevators[e].isOpen() || elevators[e].isIdle())
    return false;

  // elevator is not open or idle
  // move elevator
  else
    return elevators[e].move();
}

// member function moves idle elevator
bool Building::setIdleElevatorInMotion(int e)
{
  // check if elevator is moving
  if (!elevators[e].isIdle())
    return false;

  // elevator is idle
  else
  {
    // for loop cycles through all floors
    for (int i = 0; i < Building::FLOORS; i++)
    {
      // check if elevator's location does not match floor's elevation
      // skip if true
      if (elevators[e] != floors[i])
        continue;
    
      // check if floor's first button is up button
      if (floors[i].panel.getFirstLit() == Floor::UP) 
      { 
        // open door and set direct to up
        elevators[e].openDoorTo(i);
        elevators[e].setDirectionUp();
        return true;
      }

      // check if floor's first button is down button
      else if (floors[i].panel.getFirstLit() == Floor::DOWN) 
      {
        // open door and set direct to down
        elevators[e].openDoorTo(i);
        elevators[e].setDirectionDown();
        return true;
      }
    } 
  }

  return false;
}

// member function moves idle elevator to floor
bool Building::sendIdleElevatorToCallingFloor(int e)
 {
  // check if elevator is moving
  if (!elevators[e].isIdle())
    return false;
  
  // elevator is idle
  else 
  {
    // for loop cycles through each floor
    for (int i = 0; i < Building::FLOORS; i++)
    {
      // check if floor buttons are lit
      if (!Building::floors[i].panel.areAnyLit())
        continue;
      
      // check if floor is above elevator
      if (floors[i] > elevators[e]) 
      {
        // set direction to up and move
        elevators[e].setDirectionUp();
        elevators[e].move();
        return true;
      }

      // check if floor is below elevator
      else if (floors[i] < elevators[e]) 
      {
        // set direction to down and move
        elevators[e].setDirectionDown();
        elevators[e].move();
        return true;
      }
    }
  }

  return false; 
}

