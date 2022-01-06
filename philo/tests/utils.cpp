#include "gtest/gtest.h"
extern "C"
{
	#include "utils.h"
}

TEST(utils, atoi)
{
	EXPECT_EQ(atoi("1"), ft_atoi("1"));
	EXPECT_EQ(atoi("+1"), ft_atoi("+1"));
	EXPECT_EQ(atoi("-1"), ft_atoi("-1"));
	EXPECT_EQ(atoi("\t\v\f\r\n \f-06050"),
				ft_atoi("\t\v\f\r\n \f-06050"));
	EXPECT_EQ(atoi("\t\v\f\r\n \f- \f\t\n\r    06050"),
				ft_atoi("\t\v\f\r\n \f- \f\t\n\r    06050"));
	EXPECT_EQ(atoi("\e06050"), ft_atoi("\e06050"));
	EXPECT_EQ(atoi("-123THERE IS A NYANCAT UNDER YOUR BED"),
				ft_atoi("-123THERE IS A NYANCAT UNDER YOUR BED"));
	EXPECT_EQ(atoi("2147483647"), ft_atoi("2147483647"));
	EXPECT_EQ(atoi("-2147483648"), ft_atoi("-2147483648"));
	EXPECT_EQ(atoi("2147483648"), ft_atoi("2147483648"));
	EXPECT_EQ(atoi("-2147483649"), ft_atoi("-2147483649"));
	// EXPECT_EQ(atoi("99999999999999999999999999"),
	// 			ft_atoi("99999999999999999999999999"));
	// EXPECT_EQ(atoi("-99999999999999999999999999"),
	// 			ft_atoi("-99999999999999999999999999"));
}
