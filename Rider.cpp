// Programmer: Erin Lee
// Student id: 1805820
// File: Rider.cpp

#include "Rider.h"
#include "Building.h"

// rider constructor
Rider::Rider(int f, int t) : from(f),
                             to(t),
                             goingUp(!(Building::floors[to] < Building::floors[from])),
                             goingDown(Building::floors[to] < Building::floors[from]) {}

// overloaded assignment operator function for rider struct
Rider& Rider::operator=(const Rider& copyThis)
{
  // declare reference variable to host object
  Rider& host = *this;

  // check if host is not same as parameter
  // if not, remove const factor from host's member variables and assign to parameter's member variables
  if (this != &copyThis)
  {
    const_cast<int&>(host.from) = copyThis.from;
    const_cast<int&>(host.to) = copyThis.to;
    const_cast<bool&>(host.goingUp) = copyThis.goingUp;
    const_cast<bool&>(host.goingDown) = copyThis.goingDown;
  }

  // return reference variable
  return host;
}




