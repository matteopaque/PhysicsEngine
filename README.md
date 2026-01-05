# Physics Engine

##information

This is a project to learn about 3d physics simulation and graphics.

This is using Opengl's programmable pipeline; I learned how shaders, vertex array objects, and vertex attributes interact to produce visuals, and they amount of control they offer.
Object's vertices are loaded into the gpu, and transformation matrices are used to project them into a series of coordinate spaces, ending at 2d screen coordinates which are provided to the fragment shader.

A first person camera with mouse control and keyboard movement allows for view from different angles.

The sphere is generated procedually from a vertices on a parametric sphere, and indexed in the right order to form the proper triangles.

The physics engine is based off of a book. In it's current form it can simulate point particles, and an arbitrary number of forces on them.
The sphere in the video derives it's motion from a constant acceleration of gravity down, and a spring which produces force according to hooke's law.
