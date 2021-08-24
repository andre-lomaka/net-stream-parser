# NetStreamParser

Tcp server app accepting character stream line by line and performing analysis on incoming data.

## Requirements

- [Boost 1.77.0](https://www.boost.org/users/history/version_1_77_0.html).
- MS Visual Studio 2019.
- Netcat (e.g. [Windows binaries](https://eternallybored.org/misc/netcat/)).

## Building

- In *Configuration Properties > C/C++ > General > Additional Include Directories*, change the path to your Boost root directory, for example
`C:\Program Files\boost\boost_1_77_0`
- In *Configuration Properties > Linker > Additional Library Directories*, change the path to your Boost binaries, for example
`C:\Program Files\boost\boost_1_77_0\stage\lib`
- Open solution `net-stream-parser.sln` and build.

## Running

- Start **server** to accept data:
```
net-stream-parser port [log_file_name]
```
- Start **netcat** to transfer file:
```
nc64 localhost port < example_data.txt
```
- Analysis results will be printed in console or **log_file_name** if file name was given as server argument.
