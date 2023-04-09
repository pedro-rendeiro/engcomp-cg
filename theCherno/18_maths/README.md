## Maths
### Two main concepts
**Matrices**
A bunch of numbers that can be multiplied by something else to produce a new set of numbers. That's what transformations are.

**Vectors**
Normaly, a position at the screen.

### Math library
We will use GLM (OpenGL specific Math Lib).

### Projection matrix
Narrative:
 - Situation: we live in a 3D world.
 - Problem: our computer screen is flat (2D).
 - Solution: projection matrix makes some math to map my vertices into a 2D screen.

Types of projection:
 - Orthographic: size is not afected by distance
 - Perpective: the further the smaller 