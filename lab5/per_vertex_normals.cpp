#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"

// used tutorial slides for hints

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
	N.resize(V.rows(), 3);
	N.setZero();
	std::vector<std::vector<int> > VF;
	vertex_triangle_adjacency(F, V.rows(), VF);
	for (int i = 0; i < V.rows(); i++)
	{
		Eigen::RowVector3d normal_sum(0, 0, 0);
		for (int j = 0; j < VF[i].size(); j++)
		{
			int f = VF[i][j];
			Eigen::RowVector3d area_normal = triangle_area_normal(
				V.row(F(f, 0)),
				V.row(F(f, 1)),
				V.row(F(f, 2))
			);
			normal_sum += area_normal;
		}
		N.row(i) = normal_sum.normalized();
	}
}
