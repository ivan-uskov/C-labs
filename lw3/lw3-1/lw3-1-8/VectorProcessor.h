#pragma once

#include "stdafx.h"


bool ReadVecOfDouble(std::istream & input, std::vector<double> & buff);

double SumPositive(std::vector<double> const& vec);

void ProcessVector(std::vector<double> & vec);
void PrintVector(std::ostream & output, std::vector<double> const& vec, std::string const& delemiter);
