#include <iostream>
#include <set>

#include "util.h"

#include "DeviceData.h"

using std::cout;
using std::endl;
using std::set;

// Assumed here that time is always added first.
void DeviceData::AddTime(int sequence_number, unsigned long time)
{
   vector<SpaceTime> v;
   SpaceTime st({ 0, 0.0, 0.0, 0.0, true, true });
   spaceTimes.insert({ sequence_number, v });
   st.time = time;
   spaceTimes[sequence_number].push_back(st);
}

void DeviceData::AddCoordinates(int sequence_number, double x, double y, double z)
{
   map<int, vector<SpaceTime> >::iterator itr = spaceTimes.find(sequence_number);
   size_t last = itr->second.size() - 1;
   if (last >= 0)
   {
      itr->second[last].x = x;
      itr->second[last].y = y;
      itr->second[last].z = z;
   }
}

void DeviceData::AddQuality(int sequence_number, bool quality)
{
   size_t last = spaceTimes[sequence_number].size() - 1;
   if (last >= 0) spaceTimes[sequence_number][last].good = quality;
}

void DeviceData::AddMobility(int sequence_number, bool mobility)
{
   size_t last = spaceTimes[sequence_number].size() - 1;
   if (last >= 0) spaceTimes[sequence_number][last].moving = mobility;
}

void DeviceData::PrintDataAnalysis(std::ostream *os)
{
   OrderByTime();
   double distance, total_distance = 0.0, distance_while_moving = 0.0,
          max_speed = 0.0, speed, distance_until_time_window = 0.0;
   unsigned long time_while_moving = 0, time;
   int n_good = 0;
   vector<SpaceTime>::iterator itr, itr_prev, time_window_start, time_window_prev_start;
   for (itr = spaceTimesOrdered.begin(); itr != spaceTimesOrdered.end(); ++itr)
   {
      if (itr->good)
      {
         n_good++;
         break;
      }
   }
   if (n_good)
   {
      time_window_start = itr_prev = itr;
      ++itr;
   }
   for (; itr != spaceTimesOrdered.end(); ++itr)
   {
      if (!itr->good) continue;
      distance = getDistance(*itr_prev, *itr);
      total_distance += distance;
      if (itr->moving && itr_prev->moving)
      {
         distance_while_moving += distance;
         time = itr->time - itr_prev->time;
         time_while_moving += time;
         if ((time = itr->time - time_window_start->time) > 1000)
         {
            do
            {
               time_window_prev_start = time_window_start;
               time_window_start++;
               distance_until_time_window += getDistance(*time_window_prev_start, *time_window_start);
            } while ((time = itr->time - time_window_start->time) > 1000);
            distance = distance_while_moving - distance_until_time_window;
            speed = time ? distance / time : 0.0;
            if (speed > max_speed)
               max_speed = speed;
         }
      }
      itr_prev = itr;
      n_good++;
   }
   (*os) << "Total distance moved: " << total_distance << " meters" << endl;
   if (time_while_moving)
   {
      (*os) << "Maximum speed in the moving mode: " << 1000 * max_speed << " m/s" << endl;
      (*os) << "Average speed in the moving mode: " << 1000 * (distance_while_moving / time_while_moving) << " m/s"  << endl;
   }
   (*os) << "Number of good samples: " << n_good << endl;
   (*os) << "Number of bad samples: " << spaceTimesOrdered.size() - n_good << endl;
}

void DeviceData::OrderByTime()
{
   auto comp = [](SpaceTime x, SpaceTime y) { return x.time < y.time; };
   auto ordered_set = set<SpaceTime, decltype(comp)>(comp);
   map<int, vector<SpaceTime> >::iterator itr;
   for (itr = spaceTimes.begin(); itr != spaceTimes.end(); ++itr)
   {
      vector<SpaceTime>& v = itr->second;
      for (SpaceTime& st : v)
      {
         ordered_set.insert(st);
      }
   }
   spaceTimesOrdered.assign(ordered_set.begin(), ordered_set.end());
}
