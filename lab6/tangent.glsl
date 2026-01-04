// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  if (abs(N.z) < 0) {
	T = normalize(cross(N, vec3(1,0,0)));
  } else {
	float angle = atan(N.x, N.z);
	T = normalize(vec3(cos(angle), 0, -sin(angle)));
  }
  B = normalize(cross(N, T));

}
