// Simulator.h
// A declared simulator class used to carry out a registrar simulation program.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include "Student.h"
#include "Window.h"
#include "Queue.cpp"
#include <fstream>

using namespace std;

#ifndef Simulator_H
#define Simulator_H

class Simulator
{

  public:
    //Constructor
    Simulator();
    //Destructor
    ~Simulator();
    //Other Methods
      //Used to read in files
    void Read(string fileName);
      //Used to carry out a line simulation
    void Simulate();
      //Used to calculate student wait time and window idle time statistics
    void CalculateStats();
      //Used to output statistics
    void OutputStats();
      //Runs a cohesive program with file read-in, simulation, statistical calculation, and output.
    void Run(string fileName);
    //Helper functions
      //Used to sort arrays to make maximum and medium determination easier
    void SelectionSort(int a[], int n);
  private:
    //Reading Variables
    ifstream m_input_stream;
    string m_file_name;
    string m_single_line;
      //Used to hold the arrive time of a student
    int m_student_arrive_time;
      //Used to keep track of how many students arrive at the same time
    int m_student_pool_size;
      //Keeps track of how much time a student needs at a window
    int m_student_window_time;
      //Keeps track of how many students are left to read at a given arrival time
    int m_students_left;
      //Used to keep track of a student's position in line
    int m_student_index;
      //A boolean used to determine if we are reading an arrival time
    bool m_is_arrive_time;
      //A boolean used to determine if what we're reading in the file is the number of students
    bool m_is_number_of_students;
      //A boolean used to determine if what we're reading in the file is the wait time
    bool m_is_wait_time;
    //Stimulation Variables
      //Total number of students who will interact with the registrar at some point
    int m_number_of_students;
      //Total number of windows in the registrar
    int m_number_of_windows;
      //Keeps track of time
    int m_minutes;
      //Queue used to determine who enters a window next
    Queue<Student> m_line;
      //Array used to hold all the students who will interact with the registrar at some point
    Student* m_student_array;
      //Array used to hold all windows
    Window* m_window_array;
      //Variable used to keep track of a given student
    Student m_temporary_student;
      //Int used ot keep track of a student's position
    int m_temporary_student_position;
      //Boolean used to determine when the game is done
    bool m_simulation_done;
    //Calculate Stats Variables
      //Array used to hold student wait times
    int* m_student_wait_time_array;
    int m_mean_student_wait_time_sum;
    double m_mean_student_wait_time;
      //Array position of median wait time
    int m_median_student_wait_time_position;
    int m_median_student_wait_time;
    int m_longest_student_wait_time;
    int m_number_of_students_waiting_over_10_minutes;
      //Array used to hold window idle times
    int* m_window_idle_time_array;
    int m_mean_window_idle_time_sum;
    double m_mean_window_idle_time;
    int m_longest_window_idle_time;
    int m_number_of_windows_idle_over_5_minutes;
};

#endif
