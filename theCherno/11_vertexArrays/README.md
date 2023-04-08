## Vertex arrays
It's a data structure peculiar to OpenGL.

In compatibility moprofilede, you can ignore them. In core profile you can't though.

At end of the day, what realy happens is that a vertex array links a vertex buffer to a given layout.

### Two options when using core profile
1. Use a global VAO and specificate the layout for every buffer
2. Use a local VAO for each piece of geometry