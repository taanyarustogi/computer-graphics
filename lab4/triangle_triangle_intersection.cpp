#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

#include <Eigen/Dense>

// used tutorial slides, lecture slides, and issues page on github for reference

Eigen::Vector2d project_point_onto_uv(
    const Eigen::RowVector3d& P,
    const Eigen::RowVector3d& A0,
    const Eigen::RowVector3d& u,
    const Eigen::RowVector3d& v,
    const Eigen::Matrix2d& M)
{
    Eigen::Vector2d rhs;
    rhs[0] = u.dot(P - A0);
    rhs[1] = v.dot(P - A0);
    return M.inverse() * rhs;
}

inline double cross2d(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

inline bool point_in_triangle_2d(
    const Eigen::Vector2d& p,
    const Eigen::Vector2d& a,
    const Eigen::Vector2d& b,
    const Eigen::Vector2d& c)
{
    double s1 = cross2d(b[0] - a[0], b[1] - a[1], p[0] - a[0], p[1] - a[1]);
    double s2 = cross2d(c[0] - b[0], c[1] - b[1], p[0] - b[0], p[1] - b[1]);
    double s3 = cross2d(a[0] - c[0], a[1] - c[1], p[0] - c[0], p[1] - c[1]);

    bool has_neg = (s1 < 0) || (s2 < 0) || (s3 < 0);
    bool has_pos = (s1 > 0) || (s2 > 0) || (s3 > 0);
    return !(has_neg && has_pos);
}

bool triangle_triangle_intersection(
    const Eigen::RowVector3d& A0,
    const Eigen::RowVector3d& A1,
    const Eigen::RowVector3d& A2,
    const Eigen::RowVector3d& B0,
    const Eigen::RowVector3d& B1,
    const Eigen::RowVector3d& B2)
{
    const double epsilon = 1e-8;

    Eigen::RowVector3d normal = (A1 - A0).cross(A2 - A0);
    double norm_len = normal.norm();
    if (norm_len == 0) {
        return false;
    }
    normal = normal/norm_len;

    double d0 = (B0 - A0).dot(normal);
    double d1 = (B1 - A0).dot(normal);
    double d2 = (B2 - A0).dot(normal);

    if (d0 < epsilon && d0 > -epsilon && d1 < epsilon && d1 > -epsilon && d2 < epsilon && d2 > -epsilon)
    {
        Eigen::RowVector3d u = A1 - A0;
        Eigen::RowVector3d v = A2 - A0;

        Eigen::Matrix2d M;
        M(0, 0) = u.dot(u);
        M(0, 1) = u.dot(v);
        M(1, 0) = M(0, 1);
        M(1, 1) = v.dot(v);

        double determinant = M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0);
        if (determinant > -epsilon && determinant < epsilon) {
            return false;
        }

        Eigen::Vector2d b0 = project_point_onto_uv(B0, A0, u, v, M);
        Eigen::Vector2d b1 = project_point_onto_uv(B1, A0, u, v, M);
        Eigen::Vector2d b2 = project_point_onto_uv(B2, A0, u, v, M);


        Eigen::Vector2d a0(0, 0), a1(1, 0), a2(0, 1);

        Eigen::Vector2d A[3] = { a0, a1, a2 };
        Eigen::Vector2d B[3] = { b0, b1, b2 };

        for (int i = 0; i < 3; ++i) {
            Eigen::Vector2d p1 = A[i];
            Eigen::Vector2d p2 = A[(i + 1) % 3];
            for (int j = 0; j < 3; ++j) {
                Eigen::Vector2d q1 = B[j];
                Eigen::Vector2d q2 = B[(j + 1) % 3];

                double denom = cross2d(p2[0] - p1[0], p2[1] - p1[1], q2[0] - q1[0], q2[1] - q1[1]);
                if (denom * denom < epsilon) {
                    continue;
                }

                double s = cross2d(q1[0] - p1[0], q1[1] - p1[1], q2[0] - q1[0], q2[1] - q1[1]) / denom;
                double t = cross2d(q1[0] - p1[0], q1[1] - p1[1], p2[0] - p1[0], p2[1] - p1[1]) / denom;
                if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
                    return true;
                }
            }
        }

        for (int i = 0; i < 3; ++i) {
            if (point_in_triangle_2d(B[i], A[0], A[1], A[2])) {
                return true;
            }
            if (point_in_triangle_2d(A[i], B[0], B[1], B[2])) {
                return true;
            }
        }

        return false;
    }

    Ray a1(A0, A1 - A0);
    Ray a2(A0, A2 - A0);
    Ray a3(A1, A2 - A1);
    Ray b1(B0, B1 - B0);
    Ray b2(B0, B2 - B0);
    Ray b3(B1, B2 - B1);

    double t;
    if (ray_intersect_triangle(a1, B0, B1, B2, 0, 1, t)) {
        return true;
    }
    if (ray_intersect_triangle(a2, B0, B1, B2, 0, 1, t)) {
        return true;
    }
    if (ray_intersect_triangle(a3, B0, B1, B2, 0, 1, t)) {
        return true;
    }
    if (ray_intersect_triangle(b1, A0, A1, A2, 0, 1, t)) {
        return true;
    }
    if (ray_intersect_triangle(b2, A0, A1, A2, 0, 1, t)) {
        return true;
    } 
    if (ray_intersect_triangle(b3, A0, A1, A2, 0, 1, t)) {
        return true;
    }

    return false;
}
