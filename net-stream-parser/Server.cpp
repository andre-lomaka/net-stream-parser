#include "Session.h"

#include "Server.h"

void Server::Accept()
{
   acc.async_accept(
       [this](boost::system::error_code ec, tcp::socket socket)
       {
          if (!ec)
          {
             std::make_shared<Session>(std::move(socket), lcons)->Start();
          }
          Accept();
       }
   );
}
