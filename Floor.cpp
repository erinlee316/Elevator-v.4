// Programmer: Erin Lee
// Student id: 1805820
// File: Floor.cpp

#include "Floor.h"
#include "Rider.h"
#include "Panel.h"
#include "Building.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <climits>

// define variables for floor class static constants
const char* const Floor::UP = "Up";
const char* const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN; // defined in climits
int Floor::BOTTOM = INT_MAX; // also in climits

// constructor for floor class
Floor::Floor(const int elevation, const char* const name, const char* const label)
     : elevation(elevation), name(name), label(label)
{
  // add buttons to panel
  panel.addButton(UP);
  panel.addButton(DOWN);

  // update elevations
  if (TOP < elevation) 
    TOP = elevation;

  if (elevation < BOTTOM) 
    BOTTOM = elevation;
}

// overloaded stream insertion operator outputs info with formatted output 
ostream& operator<<(ostream& out, const Floor& floor)
{
  out.setf(ios::right);
  out.width(3);
  out << floor.label;

  out.width(15);
  out << floor.name << " at" ;
  
  out.width(6);
  out << floor.elevation << "\" Up/Down: ";
  
  out.width(2);
  out << floor.upRiders.size() << "/" << floor.downRiders.size();
  
  out.width(11);
  out << "Buttons: " << floor.panel;   
  
  // return output
  return out; 
}  

// member function adds rider to appropriate queue based on direction 
void Floor::addRider(const Rider& r)
{
  // check if rider is going up
  if (r.goingUp)
  {
    // add rider to queue that goes up
    // presses up button
    upRiders.push(r);
    panel.press(UP);
  }

  // rider wants to go down
  else
  {
    // add rider to queue that goes down
    // presses down button
    downRiders.push(r);
    panel.press(DOWN);
  }
}

// member function removes up-riders from floor
Rider Floor::removeUpRider()
{
  // check if queue for up-riders is empty
  // throw exception if empty
  if (upRiders.empty())
    throw "Up-rider queue is empty";

  // get front rider from queue and remove them
  Rider r = upRiders.front();
  upRiders.pop();
  return r;
}

// member function removes down-riders from floor
Rider Floor::removeDownRider()
{
  // check if queue for down-riders is empty
  // throw exception if empty
  if (downRiders.empty())
    throw "Down-rider queue is empty";

  // get front rider from queue and remove them
  Rider r = downRiders.front();
  downRiders.pop();
  return r;
}