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

    [-f] <input_file>           ,lance le programme avec les données dans le fichier .csv passé en paramètre
    [-p] arg1 arg2 arg3 arg4    ,arg1 : nb de véhicules abonnés, arg2 : nb de véhicules non abonnés,  
                                ,arg3 : nb de places privées, arg4 : nb de places publiques
    [-v]                        ,verbose mode
    [-h]                        ,help message
```
If you run without options, the default parameters will be used.
