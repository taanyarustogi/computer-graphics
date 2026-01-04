#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>

// an edge is a pair of ints
typedef std::pair<int, int> edge;

// need to create a hash because unordered map doesnt have for pairs
// https://www.geeksforgeeks.org/dsa/hash-table-data-structure/
// https://www.geeksforgeeks.org/cpp/unordered_map-in-cpp-stl/
struct pair_hash {
	std::size_t operator () (const edge &p) const {
		return std::hash<int>()(p.first) ^ std::hash<int>()(p.second << 16);
	}
};

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
	Eigen::MatrixXd curr_V = V;
	Eigen::MatrixXi curr_F = F;

	for(int iterations = 0; iterations < num_iters; iterations++) {
	
		Eigen::MatrixXd face_points(curr_F.rows(), 3); // num_faces x 3

		std::unordered_map<std::pair<int, int>, std::vector<int>, pair_hash> edge_to_faces; // map for the edges for each face
		std::unordered_map<std::pair<int, int>, int, pair_hash> edge_to_index; // map for the edges to their new index


		for (int i = 0; i < curr_F.rows(); i++) { // loop over faces
			Eigen::RowVector3d v0 = curr_V.row(F(i, 0));
			Eigen::RowVector3d v1 = curr_V.row(F(i, 1));
			Eigen::RowVector3d v2 = curr_V.row(F(i, 2));
			Eigen::RowVector3d v3 = curr_V.row(F(i, 3));

			face_points.row(i) = (v0 + v1 + v2 + v3) / 4.0; // step 1: average of face vertices
			for (int j = 0; j < 4; j++) { // loop over edges of face
				int v_start = F(i, j);
				int v_end = F(i, (j + 1) % 4); // v0-> v1, v1 -> v2, v2 -> v3, v3 -> v0
				edge edge = std::make_pair(std::min(v_start, v_end), std::max(v_start, v_end));
				edge_to_faces[edge].push_back(i); // add the edge to the map with the face index
			}
		}

		Eigen::MatrixXd edge_points(edge_to_faces.size(), 3); 
		int edge_index = 0;
		for (const auto& entry : edge_to_faces) { // loop over edges to compute edge points
			const edge& e = entry.first;
			const std::vector<int>& faces = entry.second;
			Eigen::RowVector3d v_start = curr_V.row(e.first);
			Eigen::RowVector3d v_end = curr_V.row(e.second);
			Eigen::RowVector3d face_point_sum(0, 0, 0);
			for (int f : faces) {
				face_point_sum += face_points.row(f);
			}

			Eigen::RowVector3d edge_point = (v_start + v_end + face_point_sum) / (2.0 + faces.size()); // step 2: average of edge vertices and face points
			edge_points.row(edge_index) = edge_point; // add edge point to edge_points
			edge_to_index[e] = edge_index; // map edge to its new index
			edge_index++;
		}

		// step 3: add edges between face points and edge points

		std::vector<Eigen::Vector4i> new_faces;
		for (int f = 0; f < curr_F.rows(); f++) {
		            Eigen::Vector4i quad = curr_F.row(f);
		            for (int j = 0; j < 4; j++) {
		                int v0 = quad(j);
		                int v1 = quad((j + 1) % 4);
		
		                std::pair<int, int> edge0 = std::make_pair(std::min(v0, v1), std::max(v0, v1));
		                std::pair<int, int> edge1 = std::make_pair(std::min(v0, quad((j + 3) % 4)), std::max(v0, quad((j + 3) % 4)));
		
		                int ep0 = curr_V.rows() + edge_to_index[edge0];
		                int ep1 = curr_V.rows() + edge_to_index[edge1];
		                int fp = curr_V.rows() + edge_points.rows() + f;
		
		                new_faces.push_back(Eigen::Vector4i(v0, ep0, fp, ep1));
		            }
		        }

		// step 4: move vertices to new poisitions
		Eigen::MatrixXd V_new(curr_V.rows(), 3); // new vertex positions

		std::vector<std::vector<int>> VF(curr_V.rows());
        for (int i = 0; i < curr_F.rows(); i++)
            for (int j = 0; j < 4; j++)
				VF[curr_F(i, j)].push_back(i); // build vertex to face adjacency

		SV.resize(curr_V.rows() + face_points.rows() + edge_points.rows(), 3);
		for (int i = 0; i < curr_V.rows(); i++) { // loop over original vertices
			
			std::vector<int> adjacent_faces = VF[i]; // get faces adjacent to vertex i
			int n = adjacent_faces.size();
			
			Eigen::RowVector3d face_point_sum(0, 0, 0);
			for (int f : adjacent_faces) { // loop over adjacent faces and sum their face points
				face_point_sum += face_points.row(f);
			}
			face_point_sum /= n;

			Eigen::RowVector3d edge_midpoint_sum(0, 0, 0);
			std::vector<int> neighbor_vertices;
			for (int f: adjacent_faces)
				for (int j = 0; j < 4; j++) { // loop over vertices of adjacent faces to find neighbor vertices
					int vertex = curr_F(f, j);
					if (vertex != i) { // exclude the original vertex
						neighbor_vertices.push_back(vertex);
					}
				}
			std::sort(neighbor_vertices.begin(), neighbor_vertices.end()); 
			neighbor_vertices.erase(std::unique(neighbor_vertices.begin(), neighbor_vertices.end()), neighbor_vertices.end()); // remove duplicates

			for (int nv : neighbor_vertices) {
				Eigen::RowVector3d neighbor_vertex = curr_V.row(nv);
				edge_midpoint_sum += (curr_V.row(i) + neighbor_vertex) / 2; // sum of midpoints of edges
			}
			edge_midpoint_sum /= neighbor_vertices.size();

			Eigen::RowVector3d new_vertex_position = (face_point_sum + 2.0 * edge_midpoint_sum + (n - 3) * curr_V.row(i)) / n; // using formula from tutorial
			V_new.row(i) = new_vertex_position; // add new vertex position 
		}

		Eigen::MatrixXd V_combined(V_new.rows() + edge_points.rows() + face_points.rows(), 3); // make new vertex matrix [V_new; edge_points; face_points]
        V_combined.topRows(V_new.rows()) = V_new; 
        V_combined.middleRows(V_new.rows(), edge_points.rows()) = edge_points;
        V_combined.bottomRows(face_points.rows()) = face_points;

        Eigen::MatrixXi F_combined(new_faces.size(), 4);
        for (int i = 0; i < new_faces.size(); i++)
			F_combined.row(i) = new_faces[i]; // convert vector of new faces to Eigen matrix

		curr_V = V_combined; // update V for next iteration
		curr_F = F_combined; // update F for next iteration
	}

	SV = curr_V; 
	SF = curr_F;
}

