## Dealing with errors
The biggest nightmare is when you run your application and gets a black screen, but no error messages.

In this situation, you have two alternatives:
 1. Cry
 2. Use error debugging stuff

There are to main error debugging stuff alternatives.

### glGetError()
Traditional way of debugging. Compatible with every (?) version of OpenGL.

### glDebugMessageCallback()
New (relative to late 2017) way of debugging. Needs OpenGL 4.3+.
