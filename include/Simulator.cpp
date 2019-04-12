// Simulator.cpp
// An implemented simulator class used to carry out a registrar simulation program.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include "Simulator.h"

using namespace std;

#ifndef Simulator_CPP
#define Simulator_CPP

//Constructor
Simulator::Simulator()
{
  m_file_name = "";
  m_single_line = "";
  m_student_arrive_time = 0;
  m_student_pool_size = 0;
  m_student_window_time = 0;
  m_students_left = 0;
  m_student_index = 1;
  m_is_arrive_time = false;
  m_is_number_of_students = false;
  m_is_wait_time = false;
  m_number_of_students = 0;
  m_number_of_windows = 0;
  m_minutes = 0;
  m_temporary_student_position = 0;
  m_simulation_done = false;
  m_mean_student_wait_time_sum = 0;
  m_mean_student_wait_time = 0.0;
  m_median_student_wait_time_position = 0;
  m_median_student_wait_time = 0;
  m_longest_student_wait_time = 0;
  m_number_of_students_waiting_over_10_minutes = 0;
  m_mean_window_idle_time_sum = 0;
  m_mean_window_idle_time = 0.0;
  m_longest_window_idle_time = 0;
  m_number_of_windows_idle_over_5_minutes = 0;
}

//Destructor
Simulator::~Simulator()
{
  //Must delete all dynamically allocated arrays
  delete[] m_window_array;
  delete[] m_student_array;
  delete[] m_student_wait_time_array;
  delete[] m_window_idle_time_array;
}

//Other Methods
void Simulator::Read(string fileName)
{
  m_file_name = fileName;
  m_input_stream.open(m_file_name);
  //This while loop is used to handle cases where we don't have a valid file
  while (m_input_stream.fail())
  {
    cout << "File does not exist!" << endl;
    cout << "Give me the name of a new file: ";
    cin >> m_file_name;
    m_input_stream.open(m_file_name);
  }
  m_input_stream >> m_number_of_windows;

  //Here, I make the window array
  m_window_array = new Window[m_number_of_windows];

  //Setting windows with their index starting at 1(I.E. 1, 2, ...)
  for (int i = 0; i < m_number_of_windows; ++i)
  {
    m_window_array[i].setWindowIndex(i+1);
  }

  //Since the next number is guaranteed to be an arrive time, I'm going to make "is arrive time" to be true
  m_is_arrive_time = true;
  m_is_number_of_students = false;
  m_is_wait_time = false;

  //Right now, I'm first going to read the file once to determine how big I need to make the student array
  while (getline(m_input_stream,m_single_line))
  {
    //This is going to go down this path by default. It will allow me to read the first number as the arrive_time and
    //then read the number of students.
    if (m_is_arrive_time == true && m_is_number_of_students == false && m_is_wait_time == false)
    {
      m_input_stream >> m_student_arrive_time;
      m_is_arrive_time = false;
      m_is_number_of_students = true;
    }
    //This goes down this path after we have already read the arrive_time. It will allow me to read the number of students.
    //at this time.
    else if (m_is_arrive_time == false && m_is_number_of_students == true && m_is_wait_time == false)
    {
      m_input_stream >> m_student_pool_size;
      m_is_number_of_students = false;
      m_is_wait_time = true;
    }
    //Finally, this will keep reading the students wait times until there are no more students at that given arrive time.
    else if (m_is_arrive_time == false && m_is_number_of_students == false && m_is_wait_time == true)
    {
      m_input_stream >> m_student_window_time;
      //This m_number_of_students variable will be used to create a student array
      m_number_of_students++;
      //the m_student_pool_size variable is to help us determine if we have read all of the students at a given arrive time
      m_student_pool_size--;
      if (m_student_pool_size == 0)
      {
        //Now we go back to reading arrive times!
        m_is_wait_time = false;
        m_is_arrive_time = true;
      }
    }
  }

  m_input_stream.close();

  //Here, we make the student array with the total number of students that we know from reading the file the first time
  m_student_array = new Student[m_number_of_students];

  //Now, I will read the file again to get the students and put them in the array
  m_input_stream.open(m_file_name);

  //This is just to catch the first number. It won't differ from the previous time that we read it.
  m_input_stream >> m_number_of_windows;

  //Again, we set out booleans.
  m_is_arrive_time = true;
  m_is_number_of_students = false;
  m_is_wait_time = false;

  while (getline(m_input_stream,m_single_line))
  {
    //Same as before
    if (m_is_arrive_time == true && m_is_number_of_students == false && m_is_wait_time == false)
    {
      m_input_stream >> m_student_arrive_time;
      m_is_arrive_time = false;
      m_is_number_of_students = true;
    }
    //Same as before
    else if (m_is_arrive_time == false && m_is_number_of_students == true && m_is_wait_time == false)
    {
      m_input_stream >> m_student_pool_size;
      m_is_number_of_students = false;
      m_is_wait_time = true;
    }
    else if (m_is_arrive_time == false && m_is_number_of_students == false && m_is_wait_time == true)
    {
      m_input_stream >> m_student_window_time;
      //Again, pool size is here to determine how long we need to keep reading students.
      m_student_pool_size--;
      if (m_student_index <= m_number_of_students)
      {
        m_student_array[m_student_index-1].setArriveTime(m_student_arrive_time);
        m_student_array[m_student_index-1].setNeededWindowTime(m_student_window_time);
        m_student_array[m_student_index-1].setLineIndex(m_student_index);
        m_student_index++;
      }
      if (m_student_pool_size == 0)
      {
        m_is_wait_time = false;
        m_is_arrive_time = true;
      }
    }
  }
  m_input_stream.close();
}

void Simulator::Simulate()
{
  //Note: m_minutes (our time variable) starts at 0
  //This loop will keep running as long as the last student in the m_student_array is not done
  while(m_simulation_done == false)
  {
    // First, I am going to put any students who are arriving in the line (queue).
    for (int i = 0; i < m_number_of_students; ++i)
    {
      if (m_student_array[i].getArriveTime() == m_minutes && m_student_array[i].getHasArrived() == false && m_student_array[i].getAtWindow() == false && m_student_array[i].getIsDone() == false)
      {
        //If the time is their arrive time and if they have all their booleans as false, I will insert them in the queue and change their boolean so that we know they have arrived.
        m_line.insert(m_student_array[i]);
        m_student_array[i].setHasArrived(true);
      }
    }
    // Now, I'm going to look through all the windows to see if there are any open for our new students who have just arrived.
    // If a window cannot be filled, then I will update its idle time.
    for (int j = 0; j < m_number_of_windows; ++j)
    {
      //This if statement will only go through if there is an empty window and if the line has a student
      if(m_window_array[j].getIsOccupied() == false && m_line.isEmpty() == false)
      {
        //I will first remove the student and make a 'temp student' variable so that I can get the student's position easily.
        m_temporary_student = m_line.remove();
        //Here is the student's position.
        m_temporary_student_position = (m_temporary_student.getLineIndex() - 1);
        //Now, I will use this position to change the status of the student in the student array - now we know they are at a window,
        //so we will set the atWindow value to be true.
        m_student_array[m_temporary_student_position].setAtWindow(true);
        //Now, I will set their window number to be that of the window that is now open
        m_student_array[m_temporary_student_position].setWindowNumber(m_window_array[j].getWindowIndex());
        //The window is now occupied, so I will set its 'is occupied' boolean to be true.
        m_window_array[j].setIsOccupied(true);
      }
      //If the window is still not occupied
      if(m_window_array[j].getIsOccupied() == false)
      {
        //We will updae its idle time
        m_window_array[j].updateIdleTime();
      }
    }

    //I will declare the simulation to be done here. If it still needs to run, then it will turn false in the following loop.
    m_simulation_done = true;

    //Now, I will evaluate the students who are at their given windows but are not done yet.
    for (int i = 0; i < m_number_of_students; ++i)
    {
      //First, I will check the students who are waiting in line. If they are still in line, I will update their wait time.
      if(m_student_array[i].getHasArrived() == true && m_student_array[i].getAtWindow() == false && m_student_array[i].getIsDone() == false)
      {
        m_student_array[i].updateWaitTime();
      }
      //Now, I will check the students who are at the windows.
      else if (m_student_array[i].getHasArrived() == true && m_student_array[i].getAtWindow() == true && m_student_array[i].getIsDone() == false)
      {
        //If they are at a window, they don't need as much window time the next round because they have been seen for 1 minute.
        m_student_array[i].updateNeededWindowTime();
        //If the student is done at the window
        if (m_student_array[i].getNeededWindowTime() == 0)
        {
          //We say that the student is 'done'
          m_student_array[i].setIsDone(true);
          //We now free the window for further use.
          m_window_array[m_student_array[i].getWindowNumber() - 1].setIsOccupied(false);
        }
      }
      //Here is where I determine if the simulation still needs to be run. If any student is not done in the array (I.E. they are in
      // line, at a window, or haven't arrived), then the simulation will turn false
      if (m_student_array[i].getIsDone() == false)
      {
        m_simulation_done = false;
      }
    }

    //Finally, we update the minutes.
    ++m_minutes;
  }
}

void Simulator::CalculateStats()
{
  //I will first make an array that holds the wait times for each student
  m_student_wait_time_array = new int[m_number_of_students];
  //Here, I fill the array with the wait times of each student and I also start determining some of the statistics
  for (int i = 0; i < m_number_of_students; ++i)
  {
    m_student_wait_time_array[i] = m_student_array[i].getWaitTime();
    //Here, I add the wait times into a sum so I can calculate the mean
    m_mean_student_wait_time_sum += m_student_wait_time_array[i];
    //Here, I determine the number of students who are waiting more than 10 minutes
    if (m_student_wait_time_array[i] > 10)
    {
      m_number_of_students_waiting_over_10_minutes++;
    }
  }

  //Here, I sort the array using the well-known SelectionSort algorithm for sorting arrays. I adapted the code from
  //another person's code online.

  SelectionSort(m_student_wait_time_array, m_number_of_students);

  //Here, I calculate the mean.
  m_mean_student_wait_time = static_cast<double>(m_mean_student_wait_time_sum)/static_cast<double>(m_number_of_students);

  //Here, I determine the median from the sorted array by determining the 'half position' within this array.
  m_median_student_wait_time_position = m_number_of_students/2;
  m_median_student_wait_time = m_student_wait_time_array[m_median_student_wait_time_position];

  //Here, I grab the longest wait time by grabbing the last element of the sorted array.
  m_longest_student_wait_time = m_student_wait_time_array[m_number_of_students - 1];

  //Here, I instantiate an array to hold window idle times.
  m_window_idle_time_array = new int[m_number_of_windows];
  //Again, I fill this window array.
  for (int j = 0; j < m_number_of_windows; ++j)
  {
    m_window_idle_time_array[j] = m_window_array[j].getIdleTime();
    //Again, a sum is computed to determine the idle time.
    m_mean_window_idle_time_sum += m_window_idle_time_array[j];
    //If the idle time is greater than 5, we add it to the number of windows over 5 minutes.
    if (m_window_idle_time_array[j] > 5)
    {
      m_number_of_windows_idle_over_5_minutes++;
    }
  }

  //The mean window idle time is computed here
  m_mean_window_idle_time = static_cast<double>(m_mean_window_idle_time_sum)/static_cast<double>(m_number_of_windows);

  //Again, the array is sorted to make pulling out the maximum easy
  SelectionSort(m_window_idle_time_array, m_number_of_windows);

  // The longest window idle time is chosen here
  m_longest_window_idle_time = m_window_idle_time_array[m_number_of_windows - 1];
}

//Used to output stats
void Simulator::OutputStats()
{
  cout << "Here are your registrar simulation statistics!" << endl;
  cout << "Mean Student Wait Time: " << m_mean_student_wait_time << endl;
  cout << "Median Student Wait Time: " << m_median_student_wait_time << endl;
  cout << "Longest Student Wait Time: " << m_longest_student_wait_time << endl;
  cout << "Number of Students waiting over 10 minutes: " << m_number_of_students_waiting_over_10_minutes << endl;
  cout << "Mean Window Idle Time: " << m_mean_window_idle_time << endl;
  cout << "Longest Window Idle Time: " << m_longest_window_idle_time << endl;
  cout << "Number of Windows idle over 5 minutes: " << m_number_of_windows_idle_over_5_minutes << endl;
}

void Simulator::Run(string fileName)
{
  Read(fileName);
  Simulate();
  CalculateStats();
  OutputStats();
}

//Well-known SelectinSort algorithm for sorting
//See read-me for reference
void Simulator::SelectionSort(int a[], int n)
{
  int i, j, min, temp;
  for (i = 0; i < n - 1; ++i) {
    min = i;
    for (j = i + 1; j < n; ++j)
    {
      if (a[j] < a[min])
      {
        min = j;
      }
    }
    temp = a[i];
    a[i] = a[min];
    a[min] = temp;
  }
}

#endif
