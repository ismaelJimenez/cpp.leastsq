// Copyright 2016 Ismael Jimenez Martinez. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "minimal_leastsq.h"
#include <math.h>
#include "assert.h"

enum BigO {
	o1,
	oN,
	oNSquared,
	oNCubed,
	oLogN,
	oNLogN
};

// Internal function to calculate the different scalability forms
std::function<double(int)> FittingCurve(BigO complexity) {
	switch (complexity) {
	case oN:
		return [](int n) {return n; };
	case oNSquared:
		return [](int n) {return n*n; };
	case oNCubed:
		return [](int n) {return n*n*n; };
	case oLogN:
		return [](int n) {return log2(n); };
	case oNLogN:
		return [](int n) {return n * log2(n); };
	case o1:
	default:
		return [](int) {return 1; };
	}
}

// Internal function to to return an string for the calculated complexity (only on automatic mode)
std::string GetBigOString(BigO complexity) {
	switch (complexity) {
	case oN:
		return "* N";
	case oNSquared:
		return "* N**2";
	case oNCubed:
		return "* N**3";
	case oLogN:
		return "* lgN";
	case oNLogN:
		return "* NlgN";
	case o1:
		return "* 1";
	default:
		return "";
	}
}

// Find the coefficient for the for the best fitting high-order term in the running time, by minimizing the sum of squares of relative error.
//   - n          : Vector containing the size of the benchmark tests.
//   - time       : Vector containing the times for the benchmark tests.

LeastSq AutoMinimalLeastSq(const std::vector<int>& n, const std::vector<double>& time) {
	assert(n.size() == time.size());
	assert(n.size() >= 2);  // Do not compute fitting curve is less than two benchmark runs are given

	std::vector<BigO> fit_curves = { oLogN, oN, oNLogN, oNSquared, oNCubed };

	LeastSq best_fit = MinimalLeastSq(n, time, FittingCurve(o1)); // Take o1 as default best fitting curve
	best_fit.complexity = GetBigOString(o1);

	// Compute all possible fitting curves and stick to the best one
	for (const auto& fit : fit_curves) {
		LeastSq current_fit = MinimalLeastSq(n, time, FittingCurve(fit));
		if (current_fit.rms < best_fit.rms) {
			best_fit = current_fit;
			best_fit.complexity = GetBigOString(fit);
		}
	}

	return best_fit;
}

// Find the coefficient for the high-order term in the running time, by minimizing the sum of squares of relative error, for the fitting curve given on the lambda expresion.
//   - n             : Vector containing the size of the benchmark tests.
//   - time          : Vector containing the times for the benchmark tests.
//   - fitting_curve : lambda expresion (e.g. [](int n) {return n; };).

LeastSq MinimalLeastSq(const std::vector<int>& n, const std::vector<double>& time, std::function<double(int)> fitting_curve) {
	double sigma_gn = 0;
	double sigma_gn_squared = 0;
	double sigma_time = 0;
	double sigma_time_gn = 0;

	// Calculate least square fitting parameter
	for (size_t i = 0; i < n.size(); ++i) {
		double gn_i = fitting_curve(n[i]);
		sigma_gn += gn_i;
		sigma_gn_squared += gn_i * gn_i;
		sigma_time += time[i];
		sigma_time_gn += time[i] * gn_i;
	}

	LeastSq result;

	// Calculate complexity.
	result.coef = sigma_time_gn / sigma_gn_squared;

	// Calculate RMS
	double rms = 0;
	for (size_t i = 0; i < n.size(); ++i) {
		double fit = result.coef * fitting_curve(n[i]);
		rms += pow((time[i] - fit), 2);
	}

	double mean = sigma_time / n.size();

	result.rms = sqrt(rms / n.size()) / mean; // Normalized RMS by the mean of the observed values

	return result;
}