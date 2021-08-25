# NetStreamParser

Tcp server app accepting character stream line by line and performing analysis on incoming data.

## Requirements

- [Boost 1.77.0](https://www.boost.org/users/history/version_1_77_0.html) or newer.
- C++14 compiler.

## Building for Windows

- Install MS Visual Studio 2019.
- In *Configuration Properties > C/C++ > General > Additional Include Directories*, change the path to your Boost root directory, for example
`C:\Program Files\boost\boost_1_77_0`.
- Open solution `net-stream-parser.sln` and build.

## Building for Linux

- Install g++, boost and cmake.
- Navigate to project root directory and enter:
```
mkdir build
cd build
cmake ..
make
```

## Running

- Start **server** to accept data:
```
net-stream-parser port [log_file_name]
```
- Start **netcat** (e.g. [Windows binaries](https://eternallybored.org/misc/netcat/)) to transfer file:
```
nc64 localhost port < example_data.txt
```
- Analysis results will be printed in console or **log_file_name** if file name was given as server argument.
