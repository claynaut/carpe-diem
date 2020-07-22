#ifndef __TASK_TEST_HPP__
#define __TASK_TEST_HPP__

#include "gtest/gtest.h"

#include "task.hpp"

TEST(TaskTest, At_Nullptr) {
    Task* test = new Task("lorem ipsum");

    ASSERT_EQ(test->at(0), nullptr);
    ASSERT_EQ(test->at(20), nullptr);
    ASSERT_EQ(test->at(-1), nullptr);
}

TEST(TaskTest, ToggleComplete) {
    Task* test = new Task("lorem ipsum");
    
    std::cout << "Initialize task..." << std::endl;
    test->display(); std::cout << std::endl;
    EXPECT_EQ(test->is_complete(), false);
    std::cout << std::endl;

    std::cout << "Toggle complete..." << std::endl;
    test->toggleComplete();
    test->display(); std::cout << std::endl;
    EXPECT_EQ(test->is_complete(), true);
    std::cout << std::endl; 

    std:: cout << "Toggle complete..." << std::endl;
    test->toggleComplete();
    test->display(); std::cout << std::endl;
    EXPECT_EQ(test->is_complete(), false);
}

TEST(TaskTest, SetGetString) {
    Task* test = new Task("lorem ipsum");

    std::cout << "Initialize task..." << std::endl;
    test->display(); std::cout << std::endl;
    EXPECT_EQ(test->getString(), "lorem ipsum");
    std::cout << std::endl;

    std::cout << "Change task name..." << std::endl;
    test->setString("hello world");
    test->display(); std::cout << std::endl;
    EXPECT_EQ(test->getString(), "hello world");
}

TEST(TaskTest, Save) {
    Task* t1 = new Task("lorem ipsum");
    Task* t2 = new Task("hello world");
    std::ofstream out;
    std::string filename = "task_test.txt";

    t1->display(); t2->display(); // expected info to write into file

    out.open(filename); out.close(); // clear file to write to

    out.open(filename, std::ios::app);
    t1->save(out);
    t2->save(out);
    out.close();
}
#endif //__TASK_TEST_HPP__
