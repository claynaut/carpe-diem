#ifndef UPPER_TEST_HPP
#define UPPER_TEST_HPP

#include "gtest/gtest.h"

#include "upper.hpp"
#include "category.hpp"
#include "task.hpp"

TEST(UpperTest, Test1) {
        Base* str1 = new Task("Eat");
        str1->display();
        std::cout << std::endl;

        Base* upper = new Upper(str1);
        upper->display();
}

TEST(UpperTest, test2) {
        Base* str1 = new Task("1");
        str1->display();
        std::cout << std::endl;

        Base* upper = new Upper(str1);
        upper->display();
}

TEST(UpperTest, Test3) {
        Category* c1 = new Category("Bucket List");
        Task* t1 = new Task("skydiving");
        Task* t2 = new Task("Las Vegas");
        Task* t3 = new Task("CONCERT");

        c1->add(t1);
        c1->add(t2);
        c1->add(t3);

        c1->display();

        Base* upper_c1 = new Upper(c1);
        upper_c1->display();

        Base* upper_t1 = new Upper(t1);
        upper_t1->display();

        Base* upper_t2 = new Upper(t2);
        upper_t2->display();

        Base* upper_t3 = new Upper(t3);
        upper_t3->display();
}
#endif
