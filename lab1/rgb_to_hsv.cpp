#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

// using this for formulas: https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
	h = 0;
	s = 0;
	v = 0;

	double rnot = r / 255.0;
	double gnot = g / 255.0;
	double bnot = b / 255.0;

	double M = std::max(rnot, std::max(gnot, bnot));
	double m = std::min(rnot, std::min(gnot, bnot));
	double C = M - m;

	if (C == 0) {
		h = 0;
	}
	else if (M == rnot) {
		double hnot = std::fmod(((gnot - bnot) / C), 6.0);
		h = 60.0 * hnot;
	}
	else if (M == gnot) {
		double hnot = (bnot - rnot) / C + 2.0;
		h = 60.0 * hnot;
	}
	else if (M == bnot) {
		double hnot = (rnot - gnot) / C + 4.0;
		h = 60.0 * hnot;
	}

	if (h < 0) {
		h += 360;
	}
	if (h > 360) {
		h -= 360;
	}

	if (M == 0) {
		s = 0;
	}
	else {
		s = C / M;
	}

	v = M;
  
}
