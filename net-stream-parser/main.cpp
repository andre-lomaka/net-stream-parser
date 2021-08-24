#include <iostream>

#include "Server.h"
#include "StreamParser.h"

int main(int argc, char *argv[])
{
   try
   {
      if (argc != 2 && argc != 3)
      {
         std::cerr << "Usage: " << argv[0] << " port [log_file_name]\n";
         return 1;
      }
      char *outfile_name = nullptr;
      if (argc == 3)
      {
         outfile_name = argv[2];
      }
      std::unique_ptr<LineConsumer> lc = std::make_unique<StreamParser>(outfile_name);
      io_context io_context;
      Server s(io_context, std::atoi(argv[1]), lc.get());
      io_context.run();
   } catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << "\n";
   }
   return 0;
}
