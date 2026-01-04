#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  for (int j = 0; j < height; j++) {
	  for (int i = 0; i < width; i++) {
		  double r = (double)rgb[3 * (j * width + i)];
		  double g = (double)rgb[3 * (j * width + i) + 1];
		  double b = (double)rgb[3 * (j * width + i) + 2];
		  double h = 0;
		  double s = 0;
		  double v = 0;
		  rgb_to_hsv(r, g, b, h, s, v);
		  h += shift;
		  if (h < 0) {
			  h += 360;
		  }
		  if (h >= 360) {
			  h -= 360;
		  }
		  hsv_to_rgb(h, s, v, r, g, b);
		  shifted[3 * (j * width + i)] = static_cast<unsigned char>(r);
		  shifted[3 * (j * width + i) + 1] = static_cast<unsigned char>(g);
		  shifted[3 * (j * width + i) + 2] = static_cast<unsigned char>(b);
	  }
  }
}
