#ifndef _STREAM_PARSER_H_
#define _STREAM_PARSER_H_

#include <map>
#include <string>
#include <fstream>

#include "LineConsumer.h"
#include "DeviceData.h"

using std::map;
using std::string;

class StreamParser : public LineConsumer
{
public:
   StreamParser(): log_file_name(nullptr) {}
   StreamParser(char *log_file): log_file_name(log_file) {}
   ~StreamParser() {}
   virtual bool ProcessLine(string& line);
   int GetNumberOfTags();
   void PrintDataAnalysis();
   void Reset();

private:
    map<uint32_t, DeviceData> tags; // maps device id to device data
    char *log_file_name;
};

#endif
