// https://mathworld.wolfram.com/SpherePointPicking.html
// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
    vec2 r = random2(seed.xy); 
    float theta = 2 * M_PI * r.y; 
    float phi = M_PI * r.x;
    float x = sin(phi) * cos(theta);
    float y = sin(phi) * sin(theta);
    float z = cos(phi);
    return normalize(vec3(x, y, z));
}
