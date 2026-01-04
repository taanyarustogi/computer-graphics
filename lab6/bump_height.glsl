// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  float noise = improved_perlin_noise(s);

  if (is_moon) {
	float noise1 = improved_perlin_noise(6 * s);
	noise = noise + 0.5 * noise1;
	noise = noise * 3;
  } else {
	float noise1 = 0.3 * improved_perlin_noise(3 * s);
    noise = noise * 0.6 + noise1;
	noise = noise * 4;
  }

	float bump = smooth_heaviside(noise, 6) * 0.1;	
	bump = clamp(bump, -0.1, 0.1);
	return bump;
}