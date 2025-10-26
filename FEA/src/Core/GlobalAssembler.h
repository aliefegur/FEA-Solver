#pragma once

#include <Eigen/Dense>
#include <vector>
#include "Element.h"

struct GlobalAssembler
{
	std::vector<BeamElement> elements;
	Eigen::MatrixXd K, M;

	int ns; // Total number of DOF

	GlobalAssembler(int ns);
	void Assemble(const Eigen::MatrixXi& de);
};
