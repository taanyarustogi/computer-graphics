#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  int index = 0;
  for (int j = 0; j < height; j++) {
	for (int i = width - 1; i >= 0; i--) {
	  for (int k = 0; k < num_channels; k++) {
		reflected[index++] = input[(j * width + i) * num_channels + k];
	  }
	}
  }
}
