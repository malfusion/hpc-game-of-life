# HPC - Conway's Game Of Life
A high performance OpenMP implementation of Conway's Game of Life with an SFML visualizer

## Demo
[![HPC - Conway's Game of Life Simulation](https://i.imgur.com/PgDOv58l.png)](https://youtu.be/XdPWb25SMo4 "HPC - Conway's Game of Life Simulation")


### Single Core Optimisation
- [ ] Force vectorisation by moving conditionals and border conditions outside
- [ ] Try Data dependency vectorization
- [ ] Move arrays to heap space and alternate using pointers
- [ ] Free allocated memory at the end of the program

### Multi Core Optimisation
- [ ] Try pragma parallel of Square slices to maximise computation and minimize data sharing/synchronisation
