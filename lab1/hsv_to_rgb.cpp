#include "hsv_to_rgb.h"
#include <cmath>

// using this for formulas: https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  r = 0;
  g = 0;
  b = 0;

  double hnot = h;

  if (h < 0) {
	  hnot += 360;
  }
  if (h >= 360) {
	  hnot -= 360;
  }

  const double C = v * s;
  const double X = C * (1 - std::abs(fmod(hnot / 60.0, 2.0) - 1.0));
  const double m = v - C;
  double rnot = 0;
  double gnot = 0;
  double bnot = 0;
  if (hnot >= 0.0 && hnot < 60.0) {
	rnot = C;
	gnot = X;
	bnot = 0;
  }
  else if (hnot >= 60.0 && hnot < 120.0) {
	rnot = X;
	gnot = C;
	bnot = 0;
  }
  else if (hnot >= 120.0 && hnot < 180.0) {
	rnot = 0;
	gnot = C;
	bnot = X;
  }
  else if (hnot >= 180.0 && hnot < 240.0) {
	rnot = 0;
	gnot = X;
	bnot = C;
  }
  else if (hnot >= 240.0 && hnot < 300.0) {
	rnot = X;
	gnot = 0;
	bnot = C;
  }
  else if (hnot >= 300.0 && hnot < 360.0) {
	rnot = C;
	gnot = 0;
	bnot = X;
  }
  r = (rnot + m) * 255.0;
  g = (gnot + m) * 255.0;
  b = (bnot + m) * 255.0;
}
