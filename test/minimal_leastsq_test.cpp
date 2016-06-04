#include <algorithm>

#include "gtest/gtest.h"
#include "minimal_leastsq.h"

TEST(minimal_leastsq_test, constant) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{7, 6, 8, 7};

  LeastSq result = MinimalLeastSq(length, time, [](int) { return 1.0; });

  EXPECT_NEAR(result.coef, 7, 0.01);
  EXPECT_NEAR(result.rms, 0.101, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLambda);
}

TEST(minimal_leastsq_test, constant_good_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{5, 5, 5, 5};

  LeastSq result = MinimalLeastSq(length, time, BigO::o1);

  EXPECT_NEAR(result.coef, 5, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::o1);
}

TEST(minimal_leastsq_test, linear) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{4, 3, 9, 13};

  LeastSq result = MinimalLeastSq(length, time, BigO::oN);

  EXPECT_NEAR(result.coef, 2.96, 0.01);
  EXPECT_NEAR(result.rms, 0.228, 0.01);
  EXPECT_EQ(result.complexity, BigO::oN);
}

TEST(minimal_leastsq_test, linear_good_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{3, 6, 9, 12};

  LeastSq result =
      MinimalLeastSq(length, time, [](int n) -> double { return n; });

  EXPECT_NEAR(result.coef, 3, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLambda);
}

TEST(minimal_leastsq_test, N_squared) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{6, 5, 7, 10};

  LeastSq result =
      MinimalLeastSq(length, time, [](int n) -> double { return n * n; });

  EXPECT_NEAR(result.coef, 0.703, 0.01);
  EXPECT_NEAR(result.rms, 0.421, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLambda);
}

TEST(minimal_leastsq_test, N_squared_good_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{1, 4, 9, 16};

  LeastSq result = MinimalLeastSq(length, time, BigO::oNSquared);

  EXPECT_NEAR(result.coef, 1, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::oNSquared);
}

TEST(minimal_leastsq_test, N_cubed) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{4, 35, 150, 390};

  LeastSq result = MinimalLeastSq(length, time, BigO::oNCubed);

  EXPECT_NEAR(result.coef, 5.99, 0.01);
  EXPECT_NEAR(result.rms, 0.064, 0.01);
  EXPECT_EQ(result.complexity, BigO::oNCubed);
}

TEST(minimal_leastsq_test, N_cubed_good_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{8, 64, 216, 512};

  LeastSq result =
      MinimalLeastSq(length, time, [](int n) -> double { return n * n * n; });

  EXPECT_NEAR(result.coef, 8, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLambda);
}

TEST(minimal_leastsq_test, logN) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{3, 22, 33, 44};

  LeastSq result =
      MinimalLeastSq(length, time, [](int n) { return std::log2(n); });

  EXPECT_NEAR(result.coef, 21.605, 0.01);
  EXPECT_NEAR(result.rms, 0.065, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLambda);
}

TEST(minimal_leastsq_test, logN_good_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{0, 8, 12, 16};

  LeastSq result = MinimalLeastSq(length, time, BigO::oLogN);

  EXPECT_NEAR(result.coef, 7.85, 0.01);
  EXPECT_NEAR(result.rms, 0.03, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLogN);
}

TEST(minimal_leastsq_test, N_logN) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{5, 40, 97, 180};

  LeastSq result = MinimalLeastSq(length, time, BigO::oNLogN);

  EXPECT_NEAR(result.coef, 21.865, 0.01);
  EXPECT_NEAR(result.rms, 0.066, 0.01);
  EXPECT_EQ(result.complexity, BigO::oNLogN);
}

TEST(minimal_leastsq_test, N_logN_good_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{0, 43, 102, 172};

  LeastSq result =
      MinimalLeastSq(length, time, [](int n) { return n * std::log2(n); });

  EXPECT_NEAR(result.coef, 21.487, 0.01);
  EXPECT_NEAR(result.rms, 0.002, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLambda);
}

TEST(minimal_leastsq_test, constant_auto_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{5, 5, 5, 5};

  LeastSq result = MinimalLeastSq(length, time, BigO::oAuto);

  EXPECT_NEAR(result.coef, 5, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::o1);
}

TEST(minimal_leastsq_test, linear_auto_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{3, 6, 9, 12};

  LeastSq result = MinimalLeastSq(length, time, BigO::oAuto);

  EXPECT_NEAR(result.coef, 3, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::oN);
}

TEST(minimal_leastsq_test, N_squared_auto_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{1, 4, 9, 16};

  LeastSq result = MinimalLeastSq(length, time, BigO::oAuto);

  EXPECT_NEAR(result.coef, 1, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::oNSquared);
}

TEST(minimal_leastsq_test, N_cubed_auto_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{8, 64, 216, 512};

  LeastSq result = MinimalLeastSq(length, time, BigO::oAuto);

  EXPECT_NEAR(result.coef, 8, 0.01);
  EXPECT_NEAR(result.rms, 0, 0.01);
  EXPECT_EQ(result.complexity, BigO::oNCubed);
}

TEST(minimal_leastsq_test, logN_cubed_auto_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{0, 8, 12, 16};

  LeastSq result = MinimalLeastSq(length, time, BigO::oAuto);

  EXPECT_NEAR(result.coef, 7.85, 0.01);
  EXPECT_NEAR(result.rms, 0.03, 0.01);
  EXPECT_EQ(result.complexity, BigO::oLogN);
}

TEST(minimal_leastsq_test, N_logN_cubed_auto_fit) {
  std::vector<int> length{1, 2, 3, 4};
  std::vector<double> time{0, 43, 102, 172};

  LeastSq result = MinimalLeastSq(length, time, BigO::oAuto);

  EXPECT_NEAR(result.coef, 21.487, 0.01);
  EXPECT_NEAR(result.rms, 0.002, 0.01);
  EXPECT_EQ(result.complexity, BigO::oNLogN);
}

TEST(minimal_leastsq_test, Big_O_String) {
  EXPECT_EQ("(1)", GetBigOString(BigO::o1));
  EXPECT_EQ("N", GetBigOString(BigO::oN));
  EXPECT_EQ("N^2", GetBigOString(BigO::oNSquared));
  EXPECT_EQ("N^3", GetBigOString(BigO::oNCubed));
  EXPECT_EQ("lgN", GetBigOString(BigO::oLogN));
  EXPECT_EQ("NlgN", GetBigOString(BigO::oNLogN));
  EXPECT_EQ("f(N)", GetBigOString(BigO::oLambda));
}
