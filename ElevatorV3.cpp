// COMSC-200
// Assignment 14 (Elevator v3)
// The instructor's solutions file
//Test driver for ElevatorSimulation version 3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "Rider.h"
#include "Building.h"
#include "Floor.h"
#include "Panel.h"
#include "Elevator.h"

int main()
{
  cout << "Programmer: Erin Lee\n"
       << "Programmer's ID: 1805820\n"
       << "File: " << __FILE__ << "\n";

  srand(time(0)); rand();
    
    for (int i = 0;; i++)
    {
        cout << "-----------------------------------------------\n";
        cout << "-- Time " << i << " ---------------------------\n";
        for (int elevator = 0; elevator < Building::ELEVATORS; elevator++)
            cout << Building::elevators[elevator] << endl;
        
        for (int floor = 0; floor < Building::FLOORS; floor++)
            cout << Building::floors[floor] << endl;

    double myArrivalRate = 1.0; // you choose!
  Building::action(i < 300 ? myArrivalRate : 0);

    cin.get();
  }
}
