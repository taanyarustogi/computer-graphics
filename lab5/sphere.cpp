#include "sphere.h"
#include <iostream>

// used https://en.wikipedia.org/wiki/Sphere and tutorial slides

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{

	int total_vertices = (num_faces_u + 1) * (num_faces_v + 1);
	int total_faces = num_faces_u * num_faces_v;
	V.resize(total_vertices, 3);
	F.resize(total_faces, 4);
	UV.resize(total_vertices, 2);
	UF.resize(total_faces, 4);
	NV.resize(total_vertices, 3);
	NF.resize(total_faces, 4);

  for (int j = 0; j <= num_faces_v; j++) {
	  double v = (double)j / num_faces_v;
	  double phi = v * 3.14159;
	  for (int i = 0; i <= num_faces_u; i++) {
		  double u = (double)i / num_faces_u;
		  double theta = u * 2.0 * 3.14159;
		  double x = sin(phi) * cos(theta);
		  double y = sin(phi) * sin(theta);
		  double z = cos(phi);
		  V.row(j * (num_faces_u + 1) + i) << x, y, z;

		  UV.row(j * (num_faces_u + 1) + i) << u, 1 - v;

		  NV.row(j * (num_faces_u + 1) + i) << x, y, z;
	  }
  }

  for (int j = 0; j < num_faces_v; j++) {
	  for (int i = 0; i < num_faces_u; i++) {
		  int v00 = j * (num_faces_u + 1) + i;
		  int v10 = j * (num_faces_u + 1) + ((i + 1) % (num_faces_u + 1));
		  int v11 = (j + 1) * (num_faces_u + 1) + ((i + 1) % (num_faces_u + 1));
		  int v01 = (j + 1) * (num_faces_u + 1) + i;
		  F.row(j * num_faces_u + i) << v00, v10, v11, v01;

		  UF.row(j * num_faces_u + i) << v00, v10, v11, v01;

		  NF.row(j * num_faces_u + i) << v00, v10, v11, v01;
	  }
  }
}
