#include "Element.h"

#include <cmath>

void BeamElement::Compute()
{
    double v1 = A * E / 5.0;
    double v2 = 12.0 * E * I / std::pow(h, 3);
    double v3 = 6.0 * E * I / std::pow(h, 2);
    double v4 = 4.0 * E * I / h;
    double v5 = 2.0 * E * I / h;

    Eigen::Matrix<double, 6, 6> KEL_L;
    KEL_L <<
        v1, 0, 0, -v1, 0, 0,
        0, v2, v3, 0, -v2, v3,
        0, v3, v4, 0, -v3, v5,
        -v1, 0, 0, v1, 0, 0,
        0, -v2, -v3, 0, v2, -v3,
        0, v3, v5, 0, -v3, v4;

    Eigen::Matrix<double, 6, 6> MEL_L;
    MEL_L <<
        140, 0, 0, 70, 0, 0,
        0, 156, 22 * h, 0, 54, -13 * h,
        0, 22 * h, 4 * h * h, 0, 13 * h, -3 * h * h,
        70, 0, 0, 140, 0, 0,
        0, 54, 13 * h, 0, 156, -22 * h,
        0, -13 * h, -3 * h * h, 0, -22 * h, 4 * h * h;

    MEL_L *= rho * A * h / 420.0;

    double c = std::cos(fi * EIGEN_PI / 180.0);
    double s = std::sin(fi * EIGEN_PI / 180.0);

    Eigen::Matrix<double, 6, 6> TEL;
    TEL <<
        c, s, 0, 0, 0, 0,
        -s, c, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, c, s, 0,
        0, 0, 0, -s, c, 0,
        0, 0, 0, 0, 0, 1;

    KEL = TEL.transpose() * KEL_L * TEL;
    MEL = TEL.transpose() * MEL_L * TEL;
}
