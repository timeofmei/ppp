#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#define PPP_EXPORT
#include "../PPP/PPP_support.h"
#undef PPP_EXPORT

using namespace PPP;
using namespace std;

#define vector Checked_vector
#define string Checked_string
#define span Checked_span
