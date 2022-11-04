#version 450 core

out vec4 FragColor;

in vec3 ourColor;
uniform vec3 sinColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
  FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0f) * vec4(sinColor, 1.0f);
}
