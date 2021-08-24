#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/asio.hpp>

#include "LineConsumer.h"

using namespace boost::asio;
using boost::asio::ip::tcp;

class Server
{
public:
   Server(io_context& io_context, short port, LineConsumer *lc):
   acc(io_context, tcp::endpoint(tcp::v4(), port)),
   lcons(lc)
   {
      Accept();
   }

private:
   void Accept();

   tcp::acceptor acc;
   LineConsumer *lcons;
};

#endif
