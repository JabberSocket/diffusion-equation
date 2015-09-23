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

## simmer

Simmer was just a 1D warm up to writing `boil`.
