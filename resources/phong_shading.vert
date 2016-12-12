#version 410 core

uniform mat4 ciModelViewProjection;
uniform mat4	ciModelView;
uniform mat4 ciView;
uniform mat4 ciProjection;

in vec4	ciPosition;
in vec3 ciNormal;

out vec3 color;

out vec3 N;
out vec3 L;
out vec3 V;

uniform vec3 light_pos = vec3(100.0, 100.0, 100.0);

void main(void)
{
  // calculate view space coordinate
  vec4 P =ciModelView * ciPosition;
  
  // calculate normal in view-space
  N = mat3(ciModelView) * ciNormal;
  
  // calculate light vector
  L = light_pos - P.xyz;
  
  // Calculate view vector
  V = -P.xyz;
  
  // calculate clip space position of each vertex
  gl_Position = ciModelViewProjection * P;
}
