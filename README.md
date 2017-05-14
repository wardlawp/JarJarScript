# JarJarScript

A scripting language project for fun.

## Coming soon

Very possibly in the future I will add...

- Memory managment (currently the program makes lots of hanging pointers)
- Variables
- Functions
- Classes
- Standard Lib
=======
![Everyone loves this guy...](http://philip-wardlaw.com/images/jarjar.png)
>>>>>>> 27329f8a38d7598b0bd54c740d1c7c10ccb8be75

## Usage

JarJarScript has a basic implementation of a Tokenizer, Parser, and Interpreter. In interactive mode it can handle basic integer arithmetic.

```bash
./JarJarScript 
>34/2+(5*4)
37
>5+5+5
15
>_
```

## Installation

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
cmake -DCMAKE_BUILD_TYPE=Debug ..
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




