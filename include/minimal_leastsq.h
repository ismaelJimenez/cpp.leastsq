#if !defined(MINIMAL_LEASTSQ_H_)
#define MINIMAL_LEASTSQ_H_

#include <vector>

// BigO is passed to a benchmark in order to specify the asymptotic computational 
// complexity for the benchmark.
enum class BigO {
  O_None,
  O_1,
  O_N,
  O_M_plus_N,
  O_N_Squared,
  O_N_Cubed,
  O_log_N,
  O_N_log_N,
  O_Auto
};

struct LeastSq {
    LeastSq() :
      coef(0),
      rms(0),
      complexity(BigO::O_None) {}

    double coef;
    double rms;
    BigO   complexity;
};

// Find the coefficient for the high-order term in the running time, by minimizing
// the sum of squares of relative error.
LeastSq minimalLeastSq(const std::vector<int>& N, const std::vector<int>& Time, BigO complexity = BigO::O_Auto);

#endif

