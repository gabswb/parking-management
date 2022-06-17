# parking-management
Simulation of a parking management using multithreading and synchronization for unix system

## Build
First, grab the source code :
```zsh
git clone https://github.com/gabswb/parking-management.git
cd parking-management
```
Then compile using the Makefile :
```zsh
make
```
## Usage 
To run the program :
```zsh
cd build
./parking-management [options]
```
```zsh
Usage : ./parking-management [-f <input_file> | -p arg1 agr2 arg3 arg4] [-v] [-h] 

    [-f] <input_file>           ,run program with data in the specified .csv file in parameter
    [-p] arg1 arg2 arg3 arg4    ,arg1 : nb of sub vehicle, arg2 : nb of non sub vehicle  
                                ,arg3 : nb of private places, arg4 : nb of public places
    [-v]                        ,verbose mode
    [-h]                        ,help message
```
If you run without options, the default parameters will be used.
