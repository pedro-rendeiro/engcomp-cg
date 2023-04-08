## Index buffers
It is a buffer that stores indices for attributes.

Exist so I don't have to store the same vertex information (such as position, color...) on GPU memory multiple times.

Instead, I can save it in an index buffer that will be called whenever I need to redraw certain vertex.

That is basicaly all the time, since everything is made up from triangles one after another (two vertices shared).

As an example, we build a square in this example.
In order to see a square, you have to make the screen squared.