// Programmer: Erin Lee
// Student id: 1805820
// File: Panel.cpp

#include "Panel.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// initialize static variable
int Panel::Button::count = 0;

// add new botton to panel
void Panel::addButton(string s)
{
  // declare and initialize variable
  Button b;
  b.label = s;
  b.lit = false;

  buttons.push_back(b);
}

// function will assign sequence to button if it meets requirements
void Panel::press(string s)
{
  // loop through all buttons in vector
  for (unsigned int i = 0; i < buttons.size( ); i++)
  {
    // check if button label matches parameter and if it lit
    if (buttons[i].label == s && !buttons[i].lit)
    {
      // set button as lit
      // assign sequence number to button
      buttons[i].lit = true;
      buttons[i].sequence = Button::count++;
    }
  }
}

// function will assign button with true or false if it meets requirements
void Panel::clear(string s)
{
  // loop through all buttons in vector
  for (unsigned int i = 0; i < buttons.size( ); i++)
  {
    // check if button label matches parameter
    if (buttons[i].label == s)

      // set button as not lit
      buttons[i].lit = false;
  }
}

// function will find first lit button in panel based on minimum sequence number
string Panel::getFirstLit() const
{
  // create button object to store minimum value 
  Button firstLit;
  bool anyLit = false;

  // loop through all buttons in vector
  for (unsigned int i = 0; i < buttons.size(); i++)
  {
    // check if button is lit and if it has lower sequence number
    if (buttons[i].lit && (!anyLit || firstLit.sequence > buttons[i].sequence))
    {
      // update info for minimum button
      firstLit = buttons[i];
      anyLit = true;      
    }
  }

  // return empty string if button is not lit
  return anyLit ? firstLit.label : "";;
}

// function will determine if button matches the parameter and if is lit or not
bool Panel::isLit(string s) const
{
  // loop through all buttons in vector
  for (unsigned int i = 0; i < buttons.size(); i++)
  {
    // check if button label matches parameter and if it is lit
    if(buttons[i].label == s && buttons[i].lit)
      return true;
  }

  // not lit
  return false;
}

// function will determine if any button is lit or not
bool Panel::areAnyLit() const
{
  // loop through all buttons in vector
  for (unsigned int i = 0; i < buttons.size(); i++)
  {
    // check if button is lit
    if (buttons[i].lit)
      return true;
  }

  // button is not lit
  return false;
}

// function will print labels for button
ostream& operator<<(ostream& out, const Panel& p)
{
  // loop through all buttons in panel object
  for (unsigned int i = 0; i < p.buttons.size(); i++)
  {
    // check if button is lit
    // if yes, output button label
    if (p.buttons[i].lit)
      out << "[" << p.buttons[i].label << "]";
  }

  // return output stream
  return out;
}