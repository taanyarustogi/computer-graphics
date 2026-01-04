#include "rgb_to_gray.h"

// using the formula from the github

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  for (int j = 0; j < height; j++) {
	for (int i = 0; i < width; i++) {
		gray[j * width + i] = 0.2126 * ((int)rgb[3 * (j * width + i)]) + 0.7152 * ((int)rgb[3 * (j * width + i) + 1]) + 0.0722 * ((int)rgb[3 * (j * width + i) + 2]);
	}
  }
}


