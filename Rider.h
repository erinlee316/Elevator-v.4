// Programmer: Erin Lee
// Student id: 1805820
// File: Rider.h

#ifndef Rider_h
#define Rider_h

// struct variable for rider
struct Rider
{
  const int from;
  const int to;
  const bool goingUp;
  const bool goingDown;
  Rider(int, int);
  Rider& operator=(const Rider&);
};

#endif