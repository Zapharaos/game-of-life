# Projet : Game of Life
    Zapharaos, Matthieu Freitag, v5.1

Implementation of a Conway's Game of life using C and Cairo. It was realized within the framework of a project in the third semester of my bachelor's degree (2020).

### Compilation with CAIRO:
____________

Compiler :
~~~{.sh}
make
~~~

On MacOS:
~~~{.sh}
make TYPE=MAC
~~~

### Compilation without CAIRO:
____________

Compile :
~~~{.sh}
make MODE=TEXTE
~~~

### Execute:
__________

~~~{.sh}
./bin/main <grid number>
~~~

**WARNING :** grid number = { 1 ; 2 ; 3 ; 4 ; 5 ; 6 ; 7 ; 8 }

### Doxygen :
____________

First of, you need to install Doxygen :
~~~{.sh}
sudo apt install doxygen
~~~

Then you can run the following :
~~~{.sh}
make doxy
~~~

### Archiving :
__________

~~~{.sh}
make dist
~~~

### Cleaning :
__________

~~~{.sh}
make clean
~~~

### Operation:
__________

- Enter => Change the grid
- n => Load a new grid from a number (1; 2; 3; 4; 5; 6; 7; 8)
- c => Activate or deactivate the cyclic counting (with or without edges)
- v => Activate or deactivate the aging
- o =-> Test if the grid is oscillating
