#ifndef LOWER_TEST_HPP
#define LOWER_TEST_HPP

#include "gtest/gtest.h"

#include "lower.hpp"
#include "category.hpp"
#include "task.hpp"

TEST(LowerTest, Test1) {
	Base* str1 = new Task("Eat");
	str1->display();	
	std::cout << std::endl;	

	Base* lower = new Lower(str1);
	lower->display();
}

TEST(LowerTest, test2) {
	Base* str1 = new Task("1");
	str1->display();
	std::cout << std::endl;

	Base* lower = new Lower(str1);
	lower->display();
}	

TEST(LowerTest, Test3) {
	Category* c1 = new Category("Shopping List");
	Task* t1 = new Task("EGGS");
	Task* t2 = new Task("mILK");
	Task* t3 = new Task("butter");
	
	c1->add(t1);
	c1->add(t2);
	c1->add(t3);

	c1->display(); 
	
	Base* lower_c1 = new Lower(c1);
	lower_c1->display();
	
	Base* lower_t1 = new Lower(t1);
	lower_t1->display();		
	
	Base* lower_t2 = new Lower(t2);
	lower_t2->display();

	Base* lower_t3 = new Lower(t3);
	lower_t3->display();
		
}

#endif
