# diffusion-equation

This repository contains some example/practice C having to do with solutions
to the diffusion equation in various scenarios.

## boil

A simple no-input 3D heat diffusion solver.

Basic physical parameters of the simulation are specifed in define
directives. This simple simulation doesn't do error checking, make sure
your parameters are sane. E.g. we do float division on length/cell-size
and cast it to an int to size the data structure.

A difference equation approach is taken to solve the diffusion equation
in three dimentions. By using static outer-volume boundary conditions we
can use just the central-difference (or Crank-Nicolson) method.
- https://en.wikipedia.org/wiki/Crank%E2%80%93Nicolson_method
- https://en.wikipedia.org/wiki/Heat_equation

It's not terribly complicated, really, but works well. In order to use
non-static boundary conditions in the outer-volume a forward and backward
Euler difference path must be added to the simulation core.

Usage: `./boil | tee boiled.logs`

Example session:
```
[00:10:08 diffusion-equation] (master)gcc boil.c -o ./boil                                                                                                                                                                         
[00:10:10 diffusion-equation] (master)./boil                                                                                                                                                                                       

Performing simulation...

Time: 000.00s Bar temperature: 
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 000.00K 000.00K 000.00K 100.00K 
100.00K 000.00K 000.00K 000.00K 100.00K 
100.00K 000.00K 000.00K 000.00K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 002.00s Bar temperature:
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 041.58K 030.48K 047.81K 100.00K 
100.00K 030.48K 015.21K 035.08K 100.00K 
100.00K 047.81K 035.08K 055.90K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 004.00s Bar temperature:
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 064.72K 056.67K 072.34K 100.00K 
100.00K 056.67K 045.82K 067.00K 100.00K 
100.00K 072.34K 067.00K 082.49K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 006.00s Bar temperature:
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 078.70K 074.62K 085.35K 100.00K 
100.00K 074.62K 070.77K 084.38K 100.00K 
100.00K 085.35K 084.38K 092.01K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 008.00s Bar temperature:
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 087.62K 086.10K 092.61K 100.00K 
100.00K 086.10K 085.21K 092.39K 100.00K 
100.00K 092.61K 092.39K 096.16K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 010.00s Bar temperature:
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 093.16K 092.78K 096.29K 100.00K 
100.00K 092.78K 092.58K 096.24K 100.00K 
100.00K 096.29K 096.24K 098.11K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Done. 
```

## simmer

Simmer was just a 1D warm up to writing `boil`.
