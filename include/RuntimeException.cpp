// RuntimeException.cpp
// A parent error class that can be implemented for a given need.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0


#include <string>
#include <iostream>

// Since we may have more than one error implement this class, we include this here a safeguard.
#ifndef RuntimeException_CPP
#define RuntimeException_CPP

using namespace std;

class RuntimeException { // generic run-time exception
  private:
    string errorMsg;
  public:
    RuntimeException( const string& err) { errorMsg = err; } string getMessage()  const {  return errorMsg; }
};

#endif
