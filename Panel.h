// Programmer: Erin Lee
// Student id: 1805820
// File: Panel.h

#ifndef Panel_h
#define Panel_h

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// class variable for panel
class Panel
{
  // struct variable for button
  struct Button
  {
    string label;
    bool lit;
    int sequence;
    static int count;
  };

  // bag of buttons
  vector<Button> buttons;

  // public access
  public:
  void addButton(string);
  void press(string);
  void clear(string);
  string getFirstLit() const;
  bool isLit(string) const;
  bool areAnyLit() const;
  friend ostream& operator<<(ostream&, const Panel&);
};

#endif