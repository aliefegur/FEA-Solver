#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include "Core/GlobalAssembler.h"
#include "Core/FEMSolver.h"

int main(int argc, char** argv)
{
	constexpr double E = 200e9;
	constexpr double rho = 7850;

	Eigen::VectorXd he(5);
	he << 0.85, 0.31, 0.31, 0.31, 0.31;

	Eigen::VectorXd fie(5);
	fie << 90, 40, 40, 140, 140;

	GlobalAssembler assembler(18);

	for (int i = 0; i < 5; ++i)
	{
		BeamElement el;
		el.E = E;
		el.rho = rho;
		el.h = he(i);
		el.fi = fie(i);
		el.A = 1e-3;
		el.I = 1e-6;
		assembler.elements.push_back(el);
	}

	Eigen::MatrixXi de(5, 6);
	de <<
		15, 16, 1, 2, 3, 4,
		5, 17, 6, 9, 10, 11,
		9, 10, 11, 2, 3, 4,
		7, 18, 8, 12, 13, 14,
		12, 13, 14, 2, 3, 4;

	assembler.Assemble(de);

	Eigen::MatrixXd Ka = assembler.K.topLeftCorner(14, 14);
	Eigen::VectorXd fa = Eigen::VectorXd::Zero(14);
	fa(5) = -6;
	fa(8) = -1100;
	fa(11) = 900 * std::cos(65.0 * EIGEN_PI / 180.0);
	fa(12) = 900 * std::sin(65.0 * EIGEN_PI / 180.0);

	FEMSolver solver;
	solver.Solve(Ka, fa);
	
	// Show deformation array
	std::cout << "da = \n" << solver.da << std::endl;

	return 0;
}
