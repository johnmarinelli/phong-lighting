#version 410

in vec3 color;
out vec4 oColor;

void main()
{
  oColor = vec4(color, 1.0);
}
