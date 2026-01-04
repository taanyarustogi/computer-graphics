#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  for (int j = 0; j < height; j++) {
	  for (int i = 0; i < width; i++) {
		  double r = (double)rgb[3 * (j * width + i)];
		  double g = (double)rgb[3 * (j * width + i) + 1];
		  double b = (double)rgb[3 * (j * width + i) + 2];
		  double h = 0;
		  double s = 0;
		  double v = 0;
		  rgb_to_hsv(r, g, b, h, s, v);
		  s *= (1 - factor);
		  if (s < 0) {
			  s = 0;
		  }
		  if (s > 1) {
			  s = 1;
		  }
		  hsv_to_rgb(h, s, v, r, g, b);
		  desaturated[3 * (j * width + i)] = static_cast<unsigned char>(r);
		  desaturated[3 * (j * width + i) + 1] = static_cast<unsigned char>(g);
		  desaturated[3 * (j * width + i) + 2] = static_cast<unsigned char>(b);
	  }
  }
}
