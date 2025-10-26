#pragma once

#include <Eigen/Dense>

struct BeamElement
{
	double	E,		// Young's modulus
			rho,	// Density
			h,		// Length
			A,		// Cross-sectional area
			I,		// Moment of inertia
			fi;		// Angle of inclination

	Eigen::Matrix<double, 6, 6>	KEL,
								MEL;

	void Compute();
};

