// Copyright 2015 Ismael Jimenez Martinez. All rights reserved.
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
#include <iostream>
#include "assert.h"

static double fittingCurve(double N, BigO complexity) {
    assert(complexity != BigO::O_None &&
            complexity != BigO::O_Auto);
    
    if(complexity == BigO::O_N_Squared)
        return N * N;
    else if(complexity == BigO::O_N)
        return N;
 
	return 1; // Default value for O_1
}

// Find the coefficient for the high-order term in the running time, by minimizing
// the sum of squares of relative error.
LeastSq minimalLeastSq(const std::vector<int>& N, const std::vector<int>& Time, BigO complexity) {
	assert(N.size() == Time.size());
    assert(complexity != BigO::O_None);

	double sigmaGN = 0;
	double sigmaGNSquared = 0;
	double sigmaTime = 0;
	double sigmaTimeGN = 0;

	for (size_t i = 0; i < N.size(); ++i) {
		double GNi = fittingCurve(N[i], complexity);
		sigmaGN += GNi;
		sigmaGNSquared += GNi * GNi;
		sigmaTime += Time[i];
		sigmaTimeGN += Time[i] * GNi;
	}

    LeastSq result;
    result.complexity = complexity;

    if(complexity != BigO::O_1)
        result.coef = sigmaTimeGN / sigmaGNSquared;
    else
        result.coef = sigmaTime / N.size();  
    
    double rms = 0; 
    for (size_t i = 0; i < N.size(); ++i) {
		double fit = result.coef * fittingCurve(N[i], complexity);
        rms += pow((Time[i] - fit), 2);
	}
    
    double mean = sigmaTime / N.size();
    
    result.rms = sqrt(rms)/mean; // Normalized RMS
    
    return result;
}