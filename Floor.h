// Programmer: Erin Lee
// Student id: 1805820
// File: Floor.h

#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <string>
#include <queue>
using namespace std;

#include "Panel.h"
#include "Rider.h"

// class variable for floor
class Floor
{
  queue<Rider> upRiders, downRiders;

  // public access
  public:
  Floor(const int, const char* const, const char* const); // elevation (inches above ground) of floor, name and label
  operator int() const {return elevation;}

  static const char* const UP;
  static const char* const DOWN;
  static int TOP, BOTTOM;

  Panel panel;
  const string name; // name of floor, for example: Mezzanine
  const string label; // as it appears on the button panel
  const int elevation; // inches above ground level

  void addRider(const Rider&); // adds a rider to floor
  bool hasUpRider() const {return !upRiders.empty();} // checks if rider is waiting to go up
  bool hasDownRider() const {return !downRiders.empty();} // checks if rider is waiting to go down
  Rider removeUpRider(); // removes an up-rider from a floor
  Rider removeDownRider(); // removes a down-rider from a floor
  unsigned int getNumberOfUpRiders() const {return upRiders.size();}
  unsigned int getNumberOfDownRiders() {return downRiders.size();}

  // for external reporting
  friend ostream& operator<<(ostream&, const Floor&); // say name, location, #'s of up/down riders waiting
};

#endif
