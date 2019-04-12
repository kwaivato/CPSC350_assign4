// Window.h
// A declared window class used to simulate windows in a registrar simulation program.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include <string>
#include <iostream>

using namespace std;

#ifndef Window_H
#define Window_H

class Window
{
  public:
    //Constructors
      //Default
    Window();
      //Overloaded
    Window(int windowIndex);
    //Destructor
    ~Window();
    //Mutators
    void setWindowIndex(int i);
    void setIdleTime(int t);
    void setIsOccupied(bool b);
    //Accessors
    int getWindowIndex();
    int getIdleTime();
    bool getIsOccupied();
    //Other methods
    void updateIdleTime();
    void print();
  private:
    //Index of window: used to tell windows apart
    int m_window_index;
    //Idle time of window
    int m_idle_time;
    //A bool that is used to tell whether a window is occupied
    bool m_is_occupied;
};

#endif
