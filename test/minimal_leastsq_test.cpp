#include <algorithm>

#include "minimal_leastsq.h"
#include "gtest/gtest.h"

TEST(minimal_leastsq_test, constant)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 7, 6, 8, 7 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_1);
    
    EXPECT_NEAR(result.coef, 7, 0.01);
    EXPECT_NEAR(result.rms, 0.101, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_1);
}

TEST(minimal_leastsq_test, constant_good_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 5, 5, 5, 5 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_1);
    
    EXPECT_NEAR(result.coef, 5, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_1);
}

TEST(minimal_leastsq_test, linear)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 4, 3, 9, 13 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N);
    
    EXPECT_NEAR(result.coef, 2.96, 0.01);
    EXPECT_NEAR(result.rms, 0.228, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N);
}

TEST(minimal_leastsq_test, linear_good_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 3, 6, 9, 12 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N);
    
    EXPECT_NEAR(result.coef, 3, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N);
}

TEST(minimal_leastsq_test, N_squared)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 6, 5, 7, 10 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_Squared);
    
    EXPECT_NEAR(result.coef, 0.703, 0.01);
    EXPECT_NEAR(result.rms, 0.421, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Squared);
}

TEST(minimal_leastsq_test, N_squared_good_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 1, 4, 9, 16 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_Squared);
    
    EXPECT_NEAR(result.coef, 1, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Squared);
}

TEST(minimal_leastsq_test, N_cubed)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 4, 35, 150, 390 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_Cubed);
    
    EXPECT_NEAR(result.coef, 5.99, 0.01);
    EXPECT_NEAR(result.rms, 0.064, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Cubed);
}

TEST(minimal_leastsq_test, N_cubed_good_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 8, 64, 216, 512 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_Cubed);
    
    EXPECT_NEAR(result.coef, 8, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Cubed);
}

TEST(minimal_leastsq_test, logN)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 3, 22, 33, 44 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_log_N);
    
    EXPECT_NEAR(result.coef, 21.605, 0.01);
    EXPECT_NEAR(result.rms, 0.065, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_log_N);
}

TEST(minimal_leastsq_test, logN_good_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 0, 8, 12, 16 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_log_N);
    
    EXPECT_NEAR(result.coef, 7.85, 0.01);
    EXPECT_NEAR(result.rms, 0.03, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_log_N);
}

TEST(minimal_leastsq_test, N_logN)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 5, 40, 97, 180 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_log_N);
    
    EXPECT_NEAR(result.coef, 21.865, 0.01);
    EXPECT_NEAR(result.rms, 0.066, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_log_N);
}

TEST(minimal_leastsq_test, N_logN_good_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 0, 43, 102, 172 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_log_N);
    
    EXPECT_NEAR(result.coef, 21.487, 0.01);
    EXPECT_NEAR(result.rms, 0.002, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_log_N);
}

TEST(minimal_leastsq_test, constant_auto_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 5, 5, 5, 5 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_Auto);
    
    EXPECT_NEAR(result.coef, 5, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_1);
}

TEST(minimal_leastsq_test, linear_auto_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 3, 6, 9, 12 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_Auto);
    
    EXPECT_NEAR(result.coef, 3, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N);
}

TEST(minimal_leastsq_test, N_squared_auto_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 1, 4, 9, 16 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_Auto);
    
    EXPECT_NEAR(result.coef, 1, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Squared);
}

TEST(minimal_leastsq_test, N_cubed_auto_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 8, 64, 216, 512 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_Auto);
    
    EXPECT_NEAR(result.coef, 8, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Cubed);
}

TEST(minimal_leastsq_test, logN_cubed_auto_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 0, 8, 12, 16 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_Auto);
    
    EXPECT_NEAR(result.coef, 7.85, 0.01);
    EXPECT_NEAR(result.rms, 0.03, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_log_N);
}

TEST(minimal_leastsq_test, N_logN_cubed_auto_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<double> Time{ 0, 43, 102, 172 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_Auto);
    
    EXPECT_NEAR(result.coef, 21.487, 0.01);
    EXPECT_NEAR(result.rms, 0.002, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_log_N);
}