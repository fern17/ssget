ssget (Simplestreams getter)
====================================
This tool allows to fetch and retrieve data from the Ubuntu Simplestreams website  
https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json

Dependencies:  
This code uses the POCO C++ libraries to download and parse the json file, https://pocoproject.org/  
The code can be compiled with CMake 3.10 or superior  
The `POCO_ROOT` environment variable has to be defined and it must point to the POCO installation folder (with subfolders `bin`, `include` and `lib`)  
The code can be tested with CMake, by running `ctest` in the build directory  

Build instructions (Linux)
------
```
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ctest
```

Build instructions (Windows)
------
Run CMake on the project  
Open Visual Studio  
Build the entire solution  
Run the ssget project to run the command line tool or  
Build the RUN_TESTS project to run tests  

The project was built and tested in Ubuntu 22.04 with G++ 11.4.0 and in Windows 11 with Microsoft Visual Studio 2022
