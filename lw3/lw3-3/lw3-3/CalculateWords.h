#include <map>
#include <string>
#include <iostream>

typedef  std::map<std::string, size_t> WordFrequencies;

WordFrequencies CalculateWordFrequencies(std::istream & stream);