#ifndef LOWER_TEST_HPP
#define LOWER_TEST_HPP

#include "gtest/gtest.h"

#include "lower.hpp"

TEST(LowerTest, Test1) {
	Base* str1 = new Task("Eat");
	str1->display();
	//EXPECT_EQ(str1->display(), "Eat");	

	Base* lower = new Lower(str1);
	//EXPECT_EQ(str1->display(), "eat");
	str1->display();
}
#endif
