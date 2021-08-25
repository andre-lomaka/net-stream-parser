#ifndef _SESSION_H_
#define _SESSION_H_

#include <memory>
#include <boost/asio.hpp>
#include <boost/regex.hpp>

#include "LineConsumer.h"

using namespace boost::asio;
using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
   Session(tcp::socket socket, LineConsumer *lc):
   sock(std::move(socket)),
   lcons(lc)
   {}

   void Start();

private:
   void Read();

   tcp::socket sock;
   enum { max_length = 1024 };
   char data[max_length] = {};
   streambuf buffer;
   boost::regex expr{"(\r|\n|\r\n)"};
   LineConsumer *lcons;
   bool eof_flag = false;
};

#endif
