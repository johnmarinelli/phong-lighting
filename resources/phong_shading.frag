#version 410 core

// output
out vec4 color;

// input from vertex shader
in vec3 N;
in vec3 L;
in vec3 V;

// material properties
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;

void main(void)
{
  // normalize n, l, v
  
  vec3 n = normalize(N);
  vec3 l = normalize(L);
  vec3 v = normalize(V);
  
  // calculate r locally
  vec3 R = reflect(-l, n);
  
  // compute diffuse & specular components for each fragment
  vec3 diffuse = max(dot(n, l), 0.0) * diffuse_albedo;
  vec3 specular = pow(max(dot(R, v), 0.0), specular_power) * specular_albedo;
  
  // write final color to framebuffer
  color = vec4(diffuse + specular, 1.0);
}
