## Blending
### What is blendind
Blending determines how we **combine** our **output** color with what is already in our **target buffer**.

 - Output: the color we output from our fragment shader (know as source)
 - Target buffer: the buffer our fragment shader is drawing to (know as destination)

### How do we control blending
Three ways:
 - glEnable(GL_BLEND) / glUnable(GL_BLEND)
 - glBlendFunc(src, dest)
    - src: multiplication factor (default is GL_ONE, i.e. keep)
    - dest: multiplication factor (default is GL_ZERO, i.e. discart)
 - glBlendEquation(mode)
    - mode: how we combine src and dest (default is GL_FUNC_ADD, i.e. sum)

What we used on the project 16 is:
 - src = GL_SRC_ALPHA
 - dest = GL_ONE_MINUS_SRC_ALPHA