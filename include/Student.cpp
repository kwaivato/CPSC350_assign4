// Student.cpp
// An implemented student class used to simulate windows in a registrar simulation program.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include "Student.h"

using namespace std;

#ifndef Student_CPP
#define Student_CPP

//Constructors
//Default
Student::Student()
{
  m_wait_time = 0;
  m_window_number = 0;
  m_has_arrived = false;
  m_at_window = false;
  m_is_done = false;
}

//Overloaded
Student::Student(int arriveTime, int neededWindowTime, int lineIndex)
{
  m_arrive_time = arriveTime;
  m_needed_window_time = neededWindowTime;
  m_line_index = lineIndex;
  m_wait_time = 0;
  m_window_number = 0;
  m_has_arrived = false;
  m_at_window = false;
  m_is_done = false;
}

//Destructor
Student::~Student()
{

}

//Mutators
void Student::setArriveTime(int t)
{
  m_arrive_time = t;
}

void Student::setWaitTime(int t)
{
  m_wait_time = t;
}

void Student::setNeededWindowTime(int t)
{
  m_needed_window_time = t;
}

void Student::setLineIndex(int i)
{
  m_line_index = i;
}

void Student::setWindowNumber(int n)
{
  m_window_number = n;
}

void Student::setHasArrived(bool b)
{
  m_has_arrived = b;
}

void Student::setAtWindow(bool b)
{
  m_at_window = b;
}

void Student::setIsDone(bool b)
{
  m_is_done = b;
}

//Accessors
int Student::getArriveTime()
{
  return m_arrive_time;
}

int Student::getWaitTime()
{
  return m_wait_time;
}

int Student::getNeededWindowTime()
{
  return m_needed_window_time;
}

int Student::getLineIndex()
{
  return m_line_index;
}

int Student::getWindowNumber()
{
  return m_window_number;
}

bool Student::getHasArrived()
{
  return m_has_arrived;
}

bool Student::getAtWindow()
{
  return m_at_window;
}

bool Student::getIsDone()
{
  return m_is_done;
}

//Other Methods
void Student::updateNeededWindowTime()
{
  //If a student is being seen at a window, their window time will decrease.
  m_needed_window_time--;
}

void Student::updateWaitTime()
{
  //If a student is in the line at the end of a cycle, they must wait and thus their wait time increases.
  m_wait_time++;
}

void Student::print()
{
  cout << "Student " << m_line_index << " Arrive Time: " << m_arrive_time << endl;
  cout << "Student " << m_line_index << " Needed Window Time: " << m_needed_window_time << endl;
  cout << "Student " << m_line_index << " Wait Time: " << m_wait_time << endl;
}

#endif
