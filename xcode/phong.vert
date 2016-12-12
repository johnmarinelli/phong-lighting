#version 410

uniform mat4 ciModelViewProjection;
uniform mat4	ciModelView;
uniform mat4 ciView;
uniform mat4 ciProjection;

in vec4	ciPosition;
in vec3 ciNormal;

out vec3 color;

void main() {
  mat4 mv_matrix = ciModelView;
  mat4 view_matrix = ciView;
  mat4 proj_matrix = ciProjection;
  vec3 normal = ciNormal;
  vec4 position = ciPosition;
  
  // light/mat properties
  vec3 light_pos = vec3(100.0, 100.0, 100.0);
  vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
  vec3 specular_albedo = vec3(0.7);
  float specular_power = 128.0;
  vec3 ambient = vec3(0.1, 0.1, 0.1);
  
  // calculate view space coordinate
  vec4 p = mv_matrix * position;
  
  // calculate normal in view space
  vec3 n = mat3(mv_matrix) * normal;
  
  // calculate view space light vector
  vec3 l = light_pos - p.xyz;
  
  // calculate view vector
  vec3 v = -p.xyz;
  
  // normalize all 3 vectors
  n = normalize(n);
  l = normalize(l);
  v = normalize(v);
  
  // calculate r by reflecting -l around plane defined by n
  vec3 r = reflect(-l, n);
  
  // calculate diffuse & specular contributions
  vec3 diffuse = max(dot(n,l), 0.0) * diffuse_albedo;
  vec3 specular = pow(max(dot(r,v), 0.0), specular_power) * specular_albedo;
  
  // send color output to fragment shader
  color = ambient + diffuse + specular;
  //color = vec3(1,1,0);
  
  // calculate clip space position of vertex
  gl_Position = ciModelViewProjection * position;
}
