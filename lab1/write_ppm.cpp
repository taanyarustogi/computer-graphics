#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
    
  std::ofstream openfile(filename);
  if(!openfile.is_open()) {
    return false;
  }
  if (num_channels == 3) {
      openfile << "P3\n";
  }
  else if (num_channels == 1) {
      openfile << "P2\n";
  }
  openfile << width << " " << height << "\n";
  openfile << "255\n";

  for(int j = 0; j < height; j++) {
    for(int i = 0; i < width; i++) {
      if(num_channels == 3) {
        openfile << (int)data[num_channels * (j * width + i)];
        openfile << " ";
        openfile << (int)data[num_channels * (j * width + i) + 1];
        openfile << " ";
        openfile << (int)data[num_channels * (j * width + i) + 2];
        openfile << " ";
      } else if(num_channels == 1) {
         openfile << (int)data[j * width + i];
         openfile << " ";
      }
    }
	openfile << "\n";
  }
  openfile.close();
  return true;
}
