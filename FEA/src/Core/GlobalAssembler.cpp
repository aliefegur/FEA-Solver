#include "GlobalAssembler.h"

GlobalAssembler::GlobalAssembler(int ns)
	:
	ns(ns)
{
	K = Eigen::MatrixXd::Zero(ns, ns);
	M = Eigen::MatrixXd::Zero(ns, ns);
}

void GlobalAssembler::Assemble(const Eigen::MatrixXi& de)
{
	for (int i = 0; i < elements.size(); ++i)
	{
		BeamElement& elem = elements[i];
		elem.Compute();

		for (int n = 0; n < 6; ++n)
		{
			for (int m = 0; m < 6; ++m)
			{
				int n1 = de(i, n) - 1;
				int n2 = de(i, m) - 1;
				K(n1, n2) += elem.KEL(n, m);
				M(n1, n2) += elem.MEL(n, m);
			}
		}
	}
}
