# JarJarScript

A scripting language project for fun. Inspired by Robert Nystrom's new book: http://www.craftinginterpreters.com/

![Everyone loves this guy...](http://philip-wardlaw.com/images/jarjar.png)

## Coming soon

- Jar Jar like syntax!

Coming in the future I will add...

- Functions (currently working on this, will be ready in August '17)
- Classes
- Standard Lib

## Usage

JarJarScript has a basic implementation of a Tokenizer, Parser, and Interpreter. 

The languge supports:

- Bools, integers, decimals, and strings.
- Arithemitic of build in types
- Conditional statements
- Loops 


```bash
./JarJarScript 
>print 33+(23/(20+3))*7;
40
>var a = "I like" + " pie";
>print a;
"I like pie"
>print 32.44 > 23.0;
ya
>{ var a = 4; print a; }
4
>print a;
"I like pie"
>ifsa(a) { var b = 2; while(b) { print a; b = b -1; } }
"I like pie"
"I like pie"
```

## Installation

### Dependencies 

- C++14
- cmake

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
cmake .. -DCMAKE_BUILD_TYPE=Debug 
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




