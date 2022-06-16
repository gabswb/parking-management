# parking-management
Simulation of a parking management 

## Compilation 
Pour compiler le programme avec le makefile :
```zsh
$ make
```
L'exectuable sera créer dans un dossier build

## Utilisation 
Après avoir compiler :
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
Exemple d'utilisation du programme : 
```bash
./parking-management -f ../sample/sample1.csv -v
```
Attention ! Comme spécifié au dessus, les options ```-p``` et ```-f``` ne sont pas compatibles.

- Si vous lancez le programme sans options, les paramètres par défaults seront utilisé : 
    - 10 places privées
    - 20 places publiques
    - 12 véhicules abonnés avec des attributs aléatoires
    - 23 véhicules non abonnés avec des attributs aléatoires
