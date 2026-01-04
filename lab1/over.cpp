#include "over.h"

// using this for the formula: https://en.wikipedia.org/wiki/Alpha_compositing

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  for (int j = 0; j < height; j++) {
	  for (int i = 0; i < width; i++) {
		  double alphaA = (double)A[4 * (j * width + i) + 3] / 255;
		  double alphaB = (double)B[4 * (j * width + i) + 3] / 255;
		  double alphaC = alphaA + alphaB * (1 - alphaA);
		  if (alphaC == 0) {
			  C[4 * (j * width + i)] = 0;
			  C[4 * (j * width + i) + 1] = 0;
			  C[4 * (j * width + i) + 2] = 0;
			  C[4 * (j * width + i) + 3] = 0;
		  }
		  else {
			  C[4 * (j * width + i)] = static_cast<unsigned char>((((double)A[4 * (j * width + i)] * alphaA) + ((double)B[4 * (j * width + i)] * alphaB * (1 - alphaA))) / alphaC);
			  C[4 * (j * width + i) + 1] = static_cast<unsigned char>((((double)A[4 * (j * width + i) + 1] * alphaA) + ((double)B[4 * (j * width + i) + 1] * alphaB * (1 - alphaA))) / alphaC);
			  C[4 * (j * width + i) + 2] = static_cast<unsigned char>((((double)A[4 * (j * width + i) + 2] * alphaA) + ((double)B[4 * (j * width + i) + 2] * alphaB * (1 - alphaA))) / alphaC);
			  C[4 * (j * width + i) + 3] = static_cast<unsigned char>(alphaC * 255);
		  }
	  }
  }
}
