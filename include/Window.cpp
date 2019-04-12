// Window.cpp
// An implemented window class used to simulate windows in a registrar simulation program.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include "Window.h"

using namespace std;

#ifndef Window_CPP
#define Window_CPP

//Constructors
//Default
Window::Window()
{
  m_window_index = 0;
  m_idle_time = 0;
  m_is_occupied = false;
}

//Overloaded
Window::Window(int windowIndex)
{
  m_window_index = windowIndex;
  m_idle_time = 0;
  m_is_occupied = false;
}

//Destructor
Window::~Window()
{

}

//Mutators
void Window::setWindowIndex(int i)
{
  m_window_index = i;
}

void Window::setIdleTime(int t)
{
  m_idle_time = t;
}

void Window::setIsOccupied(bool b)
{
  m_is_occupied = b;
}

//Accessors
int Window::getWindowIndex()
{
  return m_window_index;
}

int Window::getIdleTime()
{
  return m_idle_time;
}

bool Window::getIsOccupied()
{
  return m_is_occupied;
}

//Other Methods
void Window::updateIdleTime()
{
  //We will use this method to increase a window's idle time if it is idle
  m_idle_time++;
}

void Window::print()
{
  cout << "Idle Time of Window " << m_window_index << ": " << m_idle_time << endl;
  cout << "Occupancy Status of Window " << m_window_index << ": " << m_is_occupied << endl;
}

#endif
