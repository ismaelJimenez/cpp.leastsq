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

#if !defined(MINIMAL_LEASTSQ_H_)
#define MINIMAL_LEASTSQ_H_

#include <vector>
#include <functional>

// This data structure will contain the result returned by MinimalLeastSq
//   - coef        : Estimated coeficient for the high-order term as interpolated from data.
//   - rms         : Normalized Root Mean Squared Error.
//   - complexity  : String representing the scalability form to be shown on the output. 

struct LeastSq {
	LeastSq() :
		coef(0),
		rms(0),
		complexity("") {}

	double coef;
	double rms;
	std::string complexity;
};

// Find the coefficient for the high-order term in the running time, by minimizing the sum of squares of relative error.
LeastSq AutoMinimalLeastSq(const std::vector<int>& n, const std::vector<double>& time);

// Find the coefficient for the high-order term in the running time, by minimizing the sum of squares of relative error.
LeastSq MinimalLeastSq(const std::vector<int>& n, const std::vector<double>& time, std::function<double(int)> fitting_curve);

#endif
