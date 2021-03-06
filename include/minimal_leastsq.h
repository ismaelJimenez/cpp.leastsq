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

#include <functional>
#include <string>
#include <vector>

// BigO is passed to a benchmark in order to specify the asymptotic
// computational complexity for the benchmark. In case oAuto is selected,
// complexity will be calculated automatically to the best fit.
enum BigO { oNone, o1, oN, oNSquared, oNCubed, oLogN, oNLogN, oAuto, oLambda };

// This data structure will contain the result returned by MinimalLeastSq
//   - coef        : Estimated coeficient for the high-order term as
//                   interpolated from data.
//   - rms         : Normalized Root Mean Squared Error.
//   - complexity  : Scalability form (e.g. oN, oNLogN). In case a scalability
//                   form has been provided to MinimalLeastSq this will return
//                   the same value. In case BigO::oAuto has been selected, this
//                   parameter will return the best fitting curve detected.

struct LeastSq {
  LeastSq() : coef(0.0), rms(0.0), complexity(oNone) {}

  double coef;
  double rms;
  BigO complexity;
};

LeastSq MinimalLeastSq(const std::vector<int> &n,
                       const std::vector<double> &time, const BigO complexity);

LeastSq MinimalLeastSq(const std::vector<int> &n,
                       const std::vector<double> &time,
                       std::function<double(int)> fitting_curve);

// Function to return an string for the calculated complexity
std::string GetBigOString(BigO complexity);

#endif  // MINIMAL_LEASTSQ_H_
