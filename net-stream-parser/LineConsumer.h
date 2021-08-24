#ifndef _LINE_CONSUMER_H_
#define _LINE_CONSUMER_H_

#include <string>

using std::string;

class LineConsumer
{
public:
   virtual bool ProcessLine(string& line) = 0;
   ~LineConsumer() = default;
};

#endif
