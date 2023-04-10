#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
out vec2 v_texCoord;

uniform mat4 u_MVP;

void main()
{
   // The multiplication moves it to the appropriate space
   gl_Position = u_MVP * position;
   v_texCoord = texCoord;
};

#shader fragment
#version 330 core

#define SHOW_SQUARE 1

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor = texture(u_Texture, v_texCoord);
#if SHOW_SQUARE
   if (texColor.a > 0.0)   color = texColor;
   else                    color = u_Color;
#else
   color = texColor;
#endif
};