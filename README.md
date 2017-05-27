# JarJarScript

A scripting language project for fun. Inspired by Robert Nystrom's new book: http://www.craftinginterpreters.com/

![Everyone loves this guy...](http://philip-wardlaw.com/images/jarjar.png)

## Coming soon

Very possibly in the future I will add...

- Memory managment (currently the program makes lots of hanging pointers)
- Variables
- Functions
- Classes
- Standard Lib

## Usage

JarJarScript has a basic implementation of a Tokenizer, Parser, and Interpreter. In interactive mode it can handle basic operations for bools, integers, decimals, and strings.

```bash
./JarJarScript 
>33+(23/(20+3))*7
40
>"I like" + " pie"
"I like pie"
>32.44>23.0
ya
>ya==!na
ya
>"a">"b"
na
>!"not empty"
ya
>!0
na
```

## Installation

### Dependencies 

- c++14

*Optional:*

- GNU readline

### Instructions

Run these commands in the project root:
```bash
mkdir build
cd build
cmake .. && make
sudo make install
```

### Running Unit Tests

To run the tests:
```bash
cd build
./run_tests
```

### Building for Debug

When configuring the build directory supply this additional argument to CMake:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug ..
make clean
make
```
Your binaries are now ready for gdb.


### Configuring Eclipse Project

If you would like to use Eclipse CDT to develop JarJarScript you can run the following command from the project root:

```bash
cmake -G"Eclipse CDT4 - Unix Makefiles"
```

Note: you will have to call ```make``` from the project's root directory. This is kind of messy, but unfortunately the "Eclipse CDT4 - Unix Makefiles" 
option only supports in directory builds.


## Uninstallation

Remove the executable from /usr/local/bin.




