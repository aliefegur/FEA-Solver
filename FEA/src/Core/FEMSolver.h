#pragma once

#include <Eigen/Dense>
#include "GlobalAssembler.h"

struct FEMSolver
{
	Eigen::MatrixXd	Ka;
	Eigen::VectorXd da;
	Eigen::VectorXd fa;

	void Solve(const Eigen::MatrixXd& Ka, const Eigen::VectorXd& fa);
};
