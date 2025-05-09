# Basic Ray Tracer

Author: Jarin Thundathil
Platform: MacOS 

### TO RUN:
1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```make```
5. ```./RayTracing```

on visual studio I guess you can just hit the play button. 

### IMPLEMENTATIONS:
There are working implementations for ray-sphere, ray-plane, and ray-cylinder intersections. This is a CPU-only ray tracer so it's not very performant. I'm working on making a GPU-rendered version.

My implementation of ray-cylinder intersection borrows a lot of math from David Cobbs derivation and implementation
of Ray-Cylinder intersections. Check the comments in Shape.cpp for more info. The link for the page is:

https://davidjcobb.github.io/articles/ray-cylinder-intersection 
