## Uniforms
You don't want to hardcode all the information inside your shader. That's why you should use uniforms.

It is preaty simple:
 1. Declare the uniform insed your shader
 2. Replace your hardcoded value by your uniform
 3. On the CPU side, get the location of the uniform (glGetUniformLocation)
 4. Use that location to set the value of the uniform (glUniform{nd})