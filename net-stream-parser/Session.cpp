#include <string>
#include <boost/algorithm/string/trim.hpp>
#include <iostream> //delme
using std::cout;
#include "Session.h"

void Session::Start()
{
   eof_flag = false;
   Read();
}

void Session::Read()
{
   auto self(shared_from_this());
   async_read_until(sock, buffer, expr,
                    [this, self](boost::system::error_code ec, std::size_t length)
                    {
                       if (!ec && lcons)
                       {
                          std::istream is(&buffer);
                          std::string line;
                          getline(is, line);
                          if (eof_flag)
                             eof_flag = false;
                          else {
                             boost::algorithm::trim_right(line);
                             if (!lcons->ProcessLine(line)) return;
                          }
                          if (is.eof())
                             eof_flag = true;
                          Read();
                       }
                    });
}
