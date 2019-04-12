// ListEmpty.cpp
// An error class used to handle cases of an empty list.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include <string>
#include <iostream>
#include "RuntimeException.cpp"

using namespace std;

#ifndef ListEmpty_CPP
#define ListEmpty_CPP

// Implements the RuntimeException class
class ListEmpty : public RuntimeException {
  public:
    ListEmpty(const string& err) : RuntimeException(err) {}
};

#endif
