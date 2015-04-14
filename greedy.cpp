/*
Matthew Sheridan
greedy.cpp
13 Apr 2015

Simplifies a user-supplied fraction x/y (where x < y) via Fibonacci's greedy algorithm for Egyption
fractions, e.g.

5/6 = 1/2 + 1/3
*/

#ifndef DEBUG
#define DEBUG true
#endif

#define AUTHOR "Matthew Sheridan"
#define VERSION "1.2"
#define BUILD_DATE __DATE__

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include "dlist.h"
#include "logic.h"

using std::cout;
using std::endl;
using std::string;

const string INVALID_ARGS_POS_INT = "Arguments x, y must be non-zero, non-negative integers where x < y.";

void help();
void usage();
void version();

int main(int argc, char* argv[]) {
  long long x, y;
  sherim_data::dlist<long long>* denoms = new sherim_data::dlist<long long>();

  // Parse all args.
  try {
    // Too few or too many args.
    if (argc < 2 || argc > 3)
      throw std::invalid_argument("");

    for (int i = 1; i < argc; ++i) {
      string temp = argv[i];

      // Help option.
      if (temp.compare("-h") == 0 || temp.compare("--help") == 0) {
        help();
        return EXIT_SUCCESS;
      }

      // Check numerator and denominator.
      if (!sherim_logic::isInt(temp))
        throw std::invalid_argument(INVALID_ARGS_POS_INT);
      long long foo = std::strtol(temp.c_str(), 0, 10);
      if (foo < 1)
        throw std::invalid_argument(INVALID_ARGS_POS_INT);

      if (i == 1)
        x = foo;
      else
        y = foo;
    }
    // Enforce x < y.
    if (x >= y)
      throw std::invalid_argument(INVALID_ARGS_POS_INT);
  } catch (std::invalid_argument e) {
    usage();
    std::string error = e.what();

    if (error.length() > 0)
      cout << endl << error << endl;
    return EXIT_FAILURE;
  } catch (std::exception e) {
    cout << e.what() << endl;
    return EXIT_FAILURE;
  }

  try {
    // Expand this fraction.
    sherim_logic::greedy(x, y, denoms);
    sherim_data::ditr<long long> i = denoms->begin();

    // Iterate through results and print.
    if (i != NULL) {
      cout << x << '/' << y << " is the sum of:" << endl;
      bool comma = false;
      while (i != NULL) {
        if (comma)
          cout << ", ";
        cout << "1/" << (long long)*i;
        comma = true;
        ++i;
      }
      cout << endl;
    } else {
      cout << "No fractions found." << endl;
    }
  } catch (std::overflow_error e) {
    // Catch overflow errors caused by numbers too complex to handle with long long data type.
    cout << e.what() << endl
         << "Fraction denominator too long for data type. Try another." << endl;
  } catch (std::exception e) {
    cout << e.what() << endl;
  }

  return EXIT_SUCCESS;
}

// Post: Prints usage along with Barney-style instructions.
void help() {
  cout << "Lab 4: Egyptian fractions" << endl << endl
       << "Evaluates the greedy Egyptian expansion of a fraction x/y, where x < y. "
       << "Requires two non-zero, non-negative integers as arguments, for numerator and "
       << "denominator, respectively." << endl << endl;

  usage();
}

// Post: Print usage.
void usage() {
  cout << "Usage:" << endl
       << "  lab4 <numerator> <denominator>" << endl
       << "  Try 'lab4 --help' for more information." << endl;
}
