#include "FEMSolver.h"

void FEMSolver::Solve(const Eigen::MatrixXd& Ka, const Eigen::VectorXd& fa)
{
	this->Ka = Ka;
	this->fa = fa;
	da = Ka.colPivHouseholderQr().solve(fa);
}
