#include <algorithm>

#include "minimal_leastsq.h"
#include "gtest/gtest.h"

TEST(minimal_leastsq_test, constant)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<int> Time{ 7, 6, 8, 7 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_1);
    
    EXPECT_NEAR(result.coef, 7, 0.01);
    EXPECT_NEAR(result.rms, 0.202, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_1);
}

TEST(minimal_leastsq_test, constant_perfect_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<int> Time{ 5, 5, 5, 5 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_1);
    
    EXPECT_NEAR(result.coef, 5, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_1);
}

TEST(minimal_leastsq_test, linear)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<int> Time{ 4, 3, 9, 13 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N);
    
    EXPECT_NEAR(result.coef, 2.96, 0.01);
    EXPECT_NEAR(result.rms, 0.456, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N);
}

TEST(minimal_leastsq_test, linear_perfect_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<int> Time{ 3, 6, 9, 12 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N);
    
    EXPECT_NEAR(result.coef, 3, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N);
}

TEST(minimal_leastsq_test, squared_bad_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<int> Time{ 6, 5, 7, 10 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_Squared);
    
    EXPECT_NEAR(result.coef, 0.703, 0.01);
    EXPECT_NEAR(result.rms, 0.843, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Squared);
}

TEST(minimal_leastsq_test, squared_perfect_fit)
{    
    std::vector<int> N{ 1, 2, 3, 4 };
	std::vector<int> Time{ 1, 4, 9, 16 };

	LeastSq result = minimalLeastSq(N, Time, BigO::O_N_Squared);
    
    EXPECT_NEAR(result.coef, 1, 0.01);
    EXPECT_NEAR(result.rms, 0, 0.01);
    EXPECT_EQ(result.complexity, BigO::O_N_Squared);
}
