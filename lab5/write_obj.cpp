#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

// used https://en.wikipedia.org/wiki/Wavefront_.obj_file for reference and tutorial slides

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  std::ofstream out(filename);
  if(!out.is_open())
  {
	return false;
  }

  for (int i = 0; i < V.rows(); i++)
  {
	out << "v " << V(i,0) << " " << V(i,1) << " " << V(i,2) << "\n";
  }
  for (int i = 0; i < UV.rows(); i++)
  {
	  out << "vt " << UV(i, 0) << " " << UV(i, 1) << "\n";
  }
  for (int i = 0; i < NV.rows(); i++)
  {
	  out << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << "\n";
  }
  for (int i = 0; i < F.rows(); i++)
  {
	out << "f ";
	for (int j = 0; j < F.cols(); j++) {
		out << (F(i, j) + 1);
		if (UV.size() != 0 || NV.size() != 0) {
			out << "/";
			if (UV.size() != 0) {
				out << (UF(i, j) + 1);
			}
			if (NV.size() != 0) {
				out << "/";
				out << (NF(i, j) + 1);
			}
		}
		out << " ";
	}
	out << "\n";
  }

  return true;
}
