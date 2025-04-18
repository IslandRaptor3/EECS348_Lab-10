#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// this function checks each line of the file with a regex to verify
// it can be used as a double.
bool validate_number(const std::string &num);

//This performs the addition of two positive strings
std::string add_doubles(const std::string &a, const std::string &b);

int compare_positive(const std::string &a, const std::string &b);

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

#endif // __CALCULATOR_HPP
