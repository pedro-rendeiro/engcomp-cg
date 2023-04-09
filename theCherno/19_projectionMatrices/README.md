## Projection matrices
Narrative:
 - Situation: we live in a 3D world.
 - Problem: our computer screen is flat (2D).
 - Solution: projection matrix makes some math to map my vertices into a 2D screen.

Note: the computer screen works based on a normalized coordinates system (-1 to 1). Anything out of bounds will not be rendered. So, if we don't use a projection matrix, we need to manualy make sure that we are providing the renderer with normalized coordinates.

### Projection
Types of projection:
 - Orthographic: size is not afected by distance (usual in 2D)
 - Perpective: the further the smaller (usual in 3D)

