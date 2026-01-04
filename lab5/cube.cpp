#include "cube.h"

// used tutorial slides for hints

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  
   V.resize(8,3);
   V << 0,0,0,
		1,0,0,
		1,1,0,
		0,1,0,
		0,0,1,
		1,0,1,
		1,1,1,
	    0, 1, 1;

   F.resize(6,4);
   F << 0, 1, 5, 4, 
	   1, 2, 6, 5, 
	   2, 3, 7, 6,
	   0, 4, 7, 3, 
	   3, 2, 1, 0,
	   4, 5, 6, 7;

   UV.resize(14,2);
   UV << 0, 0.25,
	   0, 0.5,
	   0.25, 0.5,
	  0.5, 0.5,
	   0.5, 0.75,
	   0.75, 0.75,
	   0.75, 0.5,
	   1, 0.5,
	   1, 0.25,
	   0.75, 0.25,
	   0.75, 0,
	   0.5, 0,
	   0.5, 0.25,
	   0.25, 0.25;

   UF.resize(6,4);
   UF << 12, 9, 10, 11,
	   12, 3, 6, 9,
	   6, 3, 4, 5,
	   13, 0, 1, 2,
	    2, 3, 12, 13,
	   8, 9, 6, 7;

   NV.resize(6,3);
   NV << 0, -1, 0,
	   1, 0, 0,
	   0, 1, 0,
	   -1, 0, 0,
	   0, 0, -1,
	   0, 0, 1;

   NF.resize(6,4);
   NF << 0, 0, 0, 0,
	   1, 1, 1, 1,
	   2, 2, 2, 2,
	   3, 3, 3, 3,
	   4, 4, 4, 4,
	   5, 5, 5, 5;
}
