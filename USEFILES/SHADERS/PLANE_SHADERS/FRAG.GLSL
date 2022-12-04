#version 450 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform sampler2D ourTexture;

void main()
{
  FragColor = vec4(Ka, 1.0f) * texture(ourTexture, texCoord);
}
