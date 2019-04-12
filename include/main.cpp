// main.cpp
// A main program used to run a simulation of a registrar.
// @author Vidal M. Arroyo
// @author arroy118@mail.chapman.edu
// @version 1.0

#include "Simulator.h"

using namespace std;

// Main method for the entire program.
int main(int argc, char** argv)
{
  Simulator registrarSimulator;
  registrarSimulator.Run(argv[1]);
  return 0;
}
