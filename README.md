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
[23:15:03 diffussion-equation] (master)gcc boil.c -o boil
[23:15:13 diffussion-equation] (master)./boil

Performing simulation...

Time: 0.00s Bar temperature: 
100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 0.00K 0.00K 0.00K 100.00K 
100.00K 0.00K 0.00K 0.00K 100.00K 
100.00K 0.00K 0.00K 0.00K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 1.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 41.50K 30.40K 47.70K 100.00K 
100.00K 30.40K 15.15K 34.97K 100.00K 
100.00K 47.70K 34.97K 55.75K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 2.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 64.62K 56.54K 72.22K 100.00K 
100.00K 56.54K 45.66K 66.83K 100.00K 
100.00K 72.22K 66.83K 82.34K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 3.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 78.61K 74.49K 85.25K 100.00K 
100.00K 74.49K 70.58K 84.24K 100.00K 
100.00K 85.25K 84.24K 91.92K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 4.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 87.54K 85.99K 92.53K 100.00K 
100.00K 85.99K 85.06K 92.30K 100.00K 
100.00K 92.53K 92.30K 96.10K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 5.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 93.10K 92.70K 96.24K 100.00K 
100.00K 92.70K 92.47K 96.18K 100.00K 
100.00K 96.24K 96.18K 98.08K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 6.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 96.37K 96.27K 98.11K 100.00K 
100.00K 96.27K 96.21K 98.09K 100.00K 
100.00K 98.11K 98.09K 99.04K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 7.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 98.14K 98.11K 99.05K 100.00K 
100.00K 98.11K 98.09K 99.04K 100.00K 
100.00K 99.05K 99.04K 99.52K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Time: 8.00s Bar temperature: 100.00K 100.00K 100.00K 100.00K 100.00K 
100.00K 99.05K 99.05K 99.52K 100.00K 
100.00K 99.05K 99.04K 99.52K 100.00K 
100.00K 99.52K 99.52K 99.76K 100.00K 
100.00K 100.00K 100.00K 100.00K 100.00K 

Done.
```

## simmer

Simmer was just a 1D warm up to writing `boil`.
