// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
	float angle = 2 * M_PI * (animation_seconds / 8.0);
	vec4 light_pos = vec4(2*cos(angle), 1.5, 2*sin(angle), 1);
	light_pos = view * light_pos;

	vec3 n = normalize(normal_fs_in);
	vec3 v = normalize(-view_pos_fs_in.xyz);
	vec3 l = normalize(light_pos.xyz - view_pos_fs_in.xyz);
	float p = 1000;

	vec3 ka;
	vec3 kd;
	vec3 ks;

	if (is_moon) {
		ka = vec3(0.03, 0.03, 0.03);
		kd = vec3(0.5,  0.5,  0.5);
		ks = vec3(0.5,  0.5,  0.5);
	} else {
		ka = vec3(0.03, 0.03, 0.03);
		kd = vec3(0.2,  0.2,  1);
		ks = vec3(0.5,  0.5,  0.5);
	}
	
	color = blinn_phong(ka, kd, ks, p, n, v, l);
}
