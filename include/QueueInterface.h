// QueueInterface.h
// A pure virtual template class for queues.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

#ifndef QueueInterface_H
#define QueueInterface_H

class QueueInterface
{
  public:
    //Queue virtual functions
    virtual void insert(Student e) = 0;
    virtual Student remove() = 0;
    virtual Student front() = 0;
    virtual int getSize() = 0;
    virtual bool isEmpty() = 0;
};

#endif
