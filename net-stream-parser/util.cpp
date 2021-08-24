#include <iostream>

#include "util.h"

bool isHex(const char *str)
{
   return strlen(str) > 1 && str[1] == 'x';
}

double getDistance(const SpaceTime& x1, const SpaceTime& x2)
{
   double d1 = x1.x - x2.x; double d2 = x1.y - x2.y; double d3 = x1.z - x2.z;
   d1 = d1*d1; d2 = d2*d2; d3 = d3*d3;
   return sqrt(d1 + d2 + d3);
}
