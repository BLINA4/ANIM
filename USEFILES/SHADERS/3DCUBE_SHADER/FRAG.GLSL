#version 450 core

out vec4 FragColor;

in vec3 ourColor;
uniform vec3 sinColor;

void main()
{
  FragColor = vec4(ourColor, 1.0f) /* * vec4(sinColor, 1.0f) */;
}
