#include <iostream>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <cstring>

#include "util.h"
#include "StreamParser.h"

using std::cout;
using std::endl;

enum PacketType { unknown, rr_l, end_of_file, coord };

bool StreamParser::ProcessLine(string& line)
{
   if (line.compare(0, 3, "$PE")) return true;
   line_count++;
   int tok_count = 0;
   uint32_t hex_number = 0;
   int sequence_number = 0;
   string tok_prev;
   PacketType p_type = unknown;
   DeviceData d;
   map<uint32_t, DeviceData>::iterator current_tag_ptr;
   double x, y, z;
   typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
   boost::char_separator<char> sep(",", "", boost::keep_empty_tokens);
   tokenizer tokens{ line, sep };
   for (const auto& tok : tokens)
   {
      tok_count++;
      if (tok_count == 2)
      {
         if (!tok.compare("RR_L"))
         {
            p_type = rr_l;
         } else if (!tok.compare("COORD"))
         {
            p_type = coord;
         } else if (!tok.compare("EOF"))
         {
            p_type = end_of_file;
         } else
         {
            p_type = unknown;
         }
      }
      if ((p_type == unknown || p_type == end_of_file) && tok_count > 1) break;
      if (tok_count == 3)
      {
         sequence_number = atoi(tok.c_str());
      } else if (tok_count == 4)
      {
         if (isHex(tok.c_str()))
         {
            hex_number = strtoul(tok.c_str(), NULL, 0);
            tags.insert({ hex_number, d });
            current_tag_ptr = tags.find(hex_number);
         }
      } else if (tok_count > 4)
      {
         if (p_type == rr_l && tok_count % 2 == 0)
         {
            if (isHex(tok.c_str()) && !isHex(tok_prev.c_str()))
            {
               current_tag_ptr->second.AddTime(sequence_number, atol(tok_prev.c_str()));
            }
         } else if (p_type == coord)
         {
            if (tok_count == 5) x = atof(tok.c_str());
            else if (tok_count == 6) y = atof(tok.c_str());
            else if (tok_count == 7) {
               z = atof(tok.c_str());
               current_tag_ptr->second.AddCoordinates(sequence_number, x, y, z);
            } else if (tok_count == 8 && strlen(tok.c_str()) > 0)
            {
               current_tag_ptr->second.AddQuality(sequence_number, false);
            }
         }
      }
      tok_prev = tok;
   }
   if (p_type == rr_l)
   {
      hex_number = strtoul(tok_prev.c_str(), NULL, 0);
      if (hex_number) current_tag_ptr->second.AddMobility(sequence_number, false);
   } else if (p_type == end_of_file)
   {
      PrintDataAnalysis();
      Reset();
      return false;
   }
   return true;
}

int StreamParser::GetNumberOfTags()
{
   return (int)tags.size();
}

void StreamParser::PrintDataAnalysis()
{
   std::ofstream ofs;
   std::ostream *os;
   if (log_file_name)
   {
      ofs.open(log_file_name);
      os = &ofs;
   } else
   {
      os = &cout;
   }
   (*os) << "Processed " << line_count << " lines" << endl << endl;
   (*os) << "Number of devices: " << GetNumberOfTags() << endl << endl;
   map<uint32_t, DeviceData>::iterator itr;
   for (itr = tags.begin(); itr != tags.end(); ++itr)
   {
      (*os) << "Data for device " << itr->first << endl;
      DeviceData& d = itr->second;
      d.PrintDataAnalysis(os);
      (*os) << endl;
   }
   if (log_file_name)
      ofs.close();
}

void StreamParser::Reset()
{
   line_count = 0;
   tags.clear();
}
