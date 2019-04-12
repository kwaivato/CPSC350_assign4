// Student.h
// A declared student class used to simulate windows in a registrar simulation program.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include <string>
#include <iostream>

using namespace std;

#ifndef Student_H
#define Student_H

class Student
{
  public:
    //Constructors
      //Default
    Student();
      //Overloaded
    Student(int arriveTime, int neededWindowTime, int lineIndex);
    //Destructor
    ~Student();
    //Mutators
    void setArriveTime(int t);
    void setWaitTime(int t);
    void setNeededWindowTime(int t);
    void setLineIndex(int i);
    void setWindowNumber(int n);
    void setHasArrived(bool b);
    void setAtWindow(bool b);
    void setIsDone(bool b);
    //Accessors
    int getArriveTime();
    int getWaitTime();
    int getNeededWindowTime();
    int getLineIndex();
    int getWindowNumber();
    bool getHasArrived();
    bool getAtWindow();
    bool getIsDone();
    //Other Methods
    void updateNeededWindowTime();
    void updateWaitTime();
    void print();
  private:
    //Pre-determined time of arrival for each student
    int m_arrive_time;
    //How long each student waits in a line before being seen at a window
    int m_wait_time;
    //Pre-determined duration of time that each student needs at a window
    int m_needed_window_time;
    //Pre-determined index of student in each line that is especially helpful for accessing students
    int m_line_index;
    //Number of window that student spends time at
    int m_window_number;
    //Boolean used to determine if a student has arrived in the line
    bool m_has_arrived;
    //Boolean used to determine if a student is at a window
    bool m_at_window;
    //Boolean used to determine if a student is done
    bool m_is_done;
};

#endif
