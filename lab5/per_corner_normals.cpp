#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

// used tutorial slides for hints

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
	N.resize(F.rows() * F.cols(), 3);
	N.setZero();

	std::vector<std::vector<int> > VF;
	vertex_triangle_adjacency(F, V.rows(), VF);

	for (int i = 0; i < F.rows(); i++)
	{
		Eigen::RowVector3d area_normal = triangle_area_normal(
			V.row(F(i, 0)),
			V.row(F(i, 1)),
			V.row(F(i, 2))
		);

		for (int j = 0; j < F.cols(); j++)
		{
			int vertex = F(i, j);

			for (int k = 0; k < VF[vertex].size(); k++)
			{
				int f = VF[vertex][k];
				Eigen::RowVector3d adjacent_normal = triangle_area_normal(
					V.row(F(f, 0)),
					V.row(F(f, 1)),
					V.row(F(f, 2))
				);
				double angle = acos(area_normal.dot(adjacent_normal)/(area_normal.norm() * adjacent_normal.norm()));
				if (angle < (corner_threshold * 3.14159/180.0))
				{
					N((F.cols() * i + j), 0) = N((F.cols() * i + j), 0) + adjacent_normal(0);
					N((F.cols() * i + j), 1) = N((F.cols() * i + j), 1) + adjacent_normal(1);
					N((F.cols() * i + j), 2) = N((F.cols() * i + j), 2) + adjacent_normal(2);
				}
			}
			N.row(i * F.cols() + j).normalized();
		}
	}
}
