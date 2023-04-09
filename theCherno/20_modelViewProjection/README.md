## Model view projection
Model view projection matrix (or MVP matrix).

It is actualy the result of the multiplication of these three 4x4 matrices: M $\times$ V $\times$ P (mind the order).

The result of this is finaly multiplied with our vertices positions in order to produce the actual position of our objects in normalized space (-1 to 1).

We have previously studied the projection matrix. So now there are only two to go...

### Overview
Model: object's transformations*

View: camera's transformations*

*Transformations are basicaly: translation, rotation and scaling (TRS).

### Math and OpenGL standard
Normaly, the operation would be: $M\times V\times P$.

But OpenGL's API expects it to be: $P\times V\times M$. So that's what we do.