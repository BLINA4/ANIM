#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 MatrWVP;

void main()
{
  gl_Position = MatrWVP * vec4(aPos, 1.0f); 
  texCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
};

