// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  vec3 T;
  vec3 B;
  tangent(normalize(sphere_fs_in), T, B);
  vec3 dT = (bump_position(is_moon, sphere_fs_in + 0.0001*T) - bump_position(is_moon, sphere_fs_in))/0.0001;
  vec3 dB = (bump_position(is_moon, sphere_fs_in + 0.0001*B) - bump_position(is_moon, sphere_fs_in))/0.0001;

  vec3 dN = normalize(cross(dT, dB));
  mat4 model_mat = model(is_moon, animation_seconds);

  vec3 N = normalize(transpose(inverse(view)) * transpose(inverse(model_mat)) * vec4(dN,1)).xyz;

  	float angle = 2 * M_PI * (animation_seconds / 8);
	vec4 light_pos = vec4(2*cos(angle), 1.5, 2*sin(angle), 1);
	light_pos = view * light_pos;
	
	vec3 v = normalize(-view_pos_fs_in.xyz);
	vec3 l = normalize(light_pos.xyz - view_pos_fs_in.xyz);
	float p = 1000;


	vec3 ka;
	vec3 kd;
	vec3 ks;

	if (is_moon) {
		ka = vec3(0.1, 0.1, 0.1);
		kd = vec3(0.5,  0.5,  0.5);
		ks = vec3(0.5,  0.5,  0.5);
	} else {
		ka = vec3(0.1, 0.1, 0.1);
		kd = vec3(0.5,  0.5,  1);
		ks = vec3(0.5,  0.5,  0.5);
	}
	
	color = blinn_phong(ka, kd, ks, p, N, v, l) * 3;
}
