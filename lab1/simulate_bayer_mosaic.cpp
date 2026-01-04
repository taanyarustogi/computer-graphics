#include "simulate_bayer_mosaic.h"

// used information from the github

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  for (int j = 0; j < height; j++) {
	  for (int i = 0; i < width; i++) {
		  if (j % 2 == 0 && i % 2 == 0) {
			  bayer[j * width + i] = rgb[3 * (j * width + i) + 1];
		  }
		  else if (j % 2 == 0 && i % 2 == 1) {
			  bayer[j * width + i] = rgb[3 * (j * width + i) + 2];
		  }
		  else if (j % 2 == 1 && i % 2 == 0) {
			  bayer[j * width + i] = rgb[3 * (j * width + i)];
		  }
		  else if (j % 2 == 1 && i % 2 == 1) {
			  bayer[j * width + i] = rgb[3 * (j * width + i) + 1];
		  }
	  }
  }
}
