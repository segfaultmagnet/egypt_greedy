/*
Matthew Sheridan
greedy.cpp
13 Apr 2015

Simplifies a user-supplied fraction x/y (where x < y) via Fibonacci's greedy algorithm for Egyption
fractions, e.g.

5/6 = 1/2 + 1/3
*/

#ifndef DEBUG
#define DEBUG false
#endif
#ifndef OUTPUT(x)
#define OUTPUT(x) std::cout << #x << '=' << (x) << std::endl;
#endif

#define AUTHOR "Matthew Sheridan"
#define VERSION "1.2"
#define BUILD_DATE __DATE__

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "BigIntegerLibrary.hh"
#include "dlist.h"
#include "logic.h"

using std::cout;
using std::endl;
using std::string;

const string INVALID_ARGS_POS_INT = "Arguments x, y must be non-zero, non-negative integers where x < y.";

template<class T> std::string formatNumber(const T n);
void help();
void usage();
void version();

typedef BigInteger B;

int main(int argc, char* argv[]) {
  B x, y;
  sherim_data::dlist<B>* denoms = new sherim_data::dlist<B>();

  // Parse all args.
  try {
    // Too few or too many args.
    if (argc < 2 || argc > 3)
      throw std::invalid_argument("");

    for (unsigned int i = 1; i < argc; ++i) {
      string temp = argv[i];

      // Help option.
      if (temp.compare("-h") == 0 || temp.compare("--help") == 0) {
        help();
        return EXIT_SUCCESS;
      }

      // Check numerator and denominator.
      if (!sherim_logic::isInt(temp))
        throw std::invalid_argument(INVALID_ARGS_POS_INT);
      B foo = B(std::strtol(temp.c_str(), 0, 10));
      if (foo < 1)
        throw std::invalid_argument(INVALID_ARGS_POS_INT);

      // First arg is numerator, second is denominator.
      if (i == 1)
        x = B(foo);
      else
        y = B(foo);
    }
    // Enforce x < y.
    if (x >= y)
      throw std::invalid_argument(INVALID_ARGS_POS_INT);
  } catch (std::invalid_argument e) {
    // Handle problems with arguments.
    usage();
    std::string errmsg = e.what();
    if (errmsg.length() > 0)
      cout << endl << errmsg << endl;
    return EXIT_FAILURE;
  } catch (std::exception e) {
    // Catch-all.
    cout << "Error:" << endl
         << e.what() << endl;
    return EXIT_FAILURE;
  }

  // Expand this fraction.
  try {
    sherim_logic::greedy<B>(x, y, denoms);
  } catch (std::overflow_error e) {
    // Catch overflow errors caused by numbers too large to handle with data type.
    cout << "Overflow error:" << endl
         << e.what() << endl
         << "Fraction denominator too long for data type. Try another." << endl;
  } catch (std::domain_error e) {
    // Catch domain errors in greedy expansion.
    cout << "Domain error:" << endl
         << e.what() << endl;
  } catch (std::exception e) {
    // Catch-all.
    cout << "Error:" << endl
         << e.what() << endl;
  }

  // Iterate through results and print.
  sherim_data::ditr<B> i = denoms->begin();
  if (i != NULL) {
    cout << x << '/' << y << " can be expressed as the sum of "
         << denoms->size() << " fractions:" << endl << endl;
    while (i != NULL) {
      B foo = (B)*i;
      string bar = formatNumber<B>(foo);
      cout << "1/" << bar << endl;
      ++i;
    }
  } else {
    cout << "No fractions found." << endl;
  }

  return EXIT_SUCCESS;
}

// Post: Returns a string represenation of some number n, with white space between groups of five digits.
template<class T>
std::string formatNumber(const T n) {
  std::ostringstream foo;
  foo << n;
  std::string bar = foo.str();
  std::string result = "";

  for (long i = bar.length() - 1; i >= 0; --i) {
    result = bar[i] + result;
    if (i > 0 && (bar.length() - i) % 3 == 0)
      result = ' ' + result;
  }
  if (n < 0)
    result = '-' + result;

  return result;
}

// Post: Prints usage along with Barney-style instructions.
void help() {
  cout << "Greedy algorithm for the expansion of Egyptian fractions:" << endl << endl
       << "This program evaluates the greedy Egyptian expansion of a fraction x/y, where x < y. "
       << "Two non-zero, non-negative integers are requiredas arguments, representing the numerator "
       << "and denominator, respectively. "
       << "This fraction is reduced to a series of unit fractions (fractions with a numerator equal to "
       << "1, and positive integer denominator), whose sum is equal to the original."
       << endl << endl;

  usage();
}

// Post: Print usage.
void usage() {
  cout << "Usage:" << endl
       << "  greedy <numerator> <denominator>" << endl
       << "  Try 'greedy --help' for more information." << endl;
}
