#ifndef _DEVICE_DATA_H_
#define _DEVICE_DATA_H_

#include <map>
#include <vector>

using std::map;
using std::vector;

struct SpaceTime
{
   unsigned long time;
   double x, y, z;
   bool good;
   bool moving;
};

class DeviceData
{
public:
   DeviceData() {}
   ~DeviceData() {}
   void AddTime(int sequence_number, unsigned long time);
   void AddCoordinates(int sequence_number, double x, double y, double z);
   void AddQuality(int sequence_number, bool quality);
   void AddMobility(int sequence_number, bool mobility);
   void PrintDataAnalysis(std::ostream *os);

private:
   void OrderByTime();

   map<int, vector<SpaceTime> > spaceTimes;  // maps sequence id to spacetime data
   vector<SpaceTime> spaceTimesOrdered;
};

#endif
