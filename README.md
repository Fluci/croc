# croc – You never stop learning

[![Build Status](https://travis-ci.org/Fluci/croc.svg?branch=master)](https://travis-ci.org/Fluci/croc)

This repository is a collection of library classes written by me, mainly for an educational purpose. 
I try to get them clean, well tested and documented. My target is to create correctly working classes written in good C++. 

Feel free to copy, change, share, etc. 

I always love to hear critique and to improve my style.



## Some pointers to find your way in the repository

- All code can be found in `src`. `src` is split into `examples` and `lib`. 
`examples` holds single `.cpp` files which can be compiled on their own (including dependencies) and result in an executable that demonstrates what one can do with a module. 
`src` holds all the modules
- A module consists of three files: a header file `.h`, a code file `.cpp`, and a unit test file `.t.cc`. 
I use `.cc` instead of `.cpp` because it makes it easier to apply filters based on suffixes.
- The unit tests are written with `Boost.Test`.
- `.travis.yml`: configuration file to run [continuous integration](https://travis-ci.org/Fluci/croc)

## Building

I use `CMake` to control the dependencies. 
My workflow is to create a `build` folder in the root of the repository and execute `cmake ..` from inside:

``` 
mkdir build;  # create directory
cd build;     # change into it
cmake ..;     # tell CMake to prepare everything
make;         # compile the source code
```
### Dependencies
You might want to install these for successful building:

- `CMake`: kick off building process
- `Boost.Test`: required for the unit tests

