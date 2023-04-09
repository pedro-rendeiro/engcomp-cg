## Renderer
In this part, we are improving the Renderer class. That's the last abstraction we have to do in order to get rid of every piece of 'gl' calls inside our Main.cpp.

Basicaly, our Renderer does two things:
 1. Draw (based on a VA, an IB and a Shader)
 2. Clear