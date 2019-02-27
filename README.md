# Hybrid Lagrangian unstructured-Eulerian framework
Adaptive, unstructured grid, 2D framework for thermal-fluid flow simulations focused on particle transport

USES:
- Triangle: Engineering a 2D Quality Mesh Generator and Delaunay Triangulator
http://www.cs.cmu.edu/~quake/triangle.research.html
- Uthash: A hash table for C structures
https://troydhanson.github.io/uthash/


FEATURES:
- Finite Volume method
- Thermal diffusion on plates
- Multiple thermal conductivity

TODO:
- Correct fluxes based on cell's face orthogonal projection
- Add momentum transport
- Add thermal-momentum coupling
- Add particle transport
- Add adaptive grid
- Add MPI for distributed processing
