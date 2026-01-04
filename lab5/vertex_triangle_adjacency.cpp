#include "vertex_triangle_adjacency.h"

// used tutorial slides for hints

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);

  for (int i = 0; i < F.rows(); i++)
  {
	for (int j = 0; j < F.cols(); j++)
	{
	  int v = F(i, j);
	  VF[v].push_back(i);
	}
  }
  
}

