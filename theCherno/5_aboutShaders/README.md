## About shaders
### What is a shader
It is code that runs on the GPU.

There are two main types: vertex and fragment (or pixel) shaders.

### Vertex shader
It is called once per vertex and loads its attributes.

### Fragment shader
It is called once for each pixel that has to be rasterized.

Obs.: a fragment isn't exactaly a pixel, but for now it can be thought as if it was.

### Vertex X Fragment
In terms of performance, it is dangerous to put operations that require a lot of processing time in a fragment shader, since it may be called hundreds of thousends of times. A common strategy is to process most of the stuff on the vertex shader and then send it to the individual pixels in case you need. 

