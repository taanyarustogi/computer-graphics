// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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

    if (is_moon) {
        vec3 ka = vec3(0.1, 0.1, 0.1);
        vec3 kd = vec3(0.5,  0.5,  0.5);
        vec3 ks = vec3(0.5,  0.5,  0.5);
        color = blinn_phong(ka, kd, ks, p, N, v, l);
        return;
    }

    float t = animation_seconds * 0.5;

    float n1 = improved_perlin_noise(1.5 * sphere_fs_in + vec3(t));
    float n2 = improved_perlin_noise(5 * sphere_fs_in);
    float n = n1+n2;

    n = clamp((n + 1) * 0.5, -1, 1); 

    float lava_mask = smoothstep(0.2, 0.6, n); 

    vec3 lava = vec3(1, 0, 0.05);   
    vec3 crust = vec3(0.15, 0.05, 0); 
    vec3 kd = mix(lava, crust, lava_mask);

    float flicker = 0.5 + sin(animation_seconds + n);
    kd = mix(kd, lava, (1.0 - lava_mask) * 0.5 * flicker);

    vec3 ka = kd * 0.3;
    vec3 ks = vec3(0.5, 0.5, 0.5);

    color = blinn_phong(ka, kd, ks, p, N, v, l) * 3;
}
