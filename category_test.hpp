#ifndef __CATEGORY_TEST_HPP__
#define __CATEGORY_TEST_HPP__

#include "gtest/gtest.h"

#include "category.hpp"

TEST(CategoryTest, AddChildren) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");

    std::cout << "Initialize category..." << std::endl;   
    c1->display();
    EXPECT_EQ(c1->getSize(), 0);
    std::cout << std::endl;

    std::cout << "Add children..." << std::endl;
    c1->add(t1);
    c1->add(t2);
    c1->display();
    EXPECT_EQ(c1->getSize(), 2);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
}

TEST(CategoryTest, RemoveChildren_Middle) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello");
    Task* t4 = new Task("world");
 
    c1->add(t1);
    c1->add(t2);
    c1->add(t3);
    c1->add(t4);

    std::cout << "Create category with children..." << std::endl;
    c1->display();
    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    EXPECT_EQ(c1->at(3)->getString(), "world");
    std::cout << std::endl;

    std::cout << "Remove task 2..." << std::endl;
    c1->remove(1);
    c1->display();
    EXPECT_EQ(c1->getSize(), 3);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "hello");
    EXPECT_EQ(c1->at(2)->getString(), "world");
}

TEST(CategoryTest, RemoveChildren_First) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello");
    Task* t4 = new Task("world");

    c1->add(t1);
    c1->add(t2);
    c1->add(t3);
    c1->add(t4);

    std::cout << "Create category with children..." << std::endl;
    c1->display();
    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    EXPECT_EQ(c1->at(3)->getString(), "world");
    std::cout << std::endl;

    std::cout << "Remove task 1..." << std::endl;
    c1->remove(0);
    c1->display();
    EXPECT_EQ(c1->getSize(), 3);
    EXPECT_EQ(c1->at(0)->getString(), "ipsum");
    EXPECT_EQ(c1->at(1)->getString(), "hello");
    EXPECT_EQ(c1->at(2)->getString(), "world");
}

TEST(CategoryTest, RemoveChildren_Last) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello");
    Task* t4 = new Task("world");

    c1->add(t1);
    c1->add(t2);
    c1->add(t3);
    c1->add(t4);

    std::cout << "Create category with children..." << std::endl;
    c1->display();
    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    EXPECT_EQ(c1->at(3)->getString(), "world");
    std::cout << std::endl;

    std::cout << "Remove task 4..." << std::endl;
    c1->remove(3);
    c1->display();
    EXPECT_EQ(c1->getSize(), 3);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
}

TEST(CategoryTest, RemoveChildren_Invalid) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello");
    Task* t4 = new Task("world");

    c1->add(t1);
    c1->add(t2);
    c1->add(t3);
    c1->add(t4);

    std::cout << "Create category with children..." << std::endl;
    c1->display();
    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    EXPECT_EQ(c1->at(3)->getString(), "world");
    std::cout << std::endl;

    std::cout << "Remove task 5..." << std::endl;
    c1->remove(5);
    c1->display();
    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    EXPECT_EQ(c1->at(3)->getString(), "world");
    std::cout << std::endl;

    std::cout << "Remove task -1..." << std::endl;
    c1->remove(-1);
    c1->display();
    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    EXPECT_EQ(c1->at(3)->getString(), "world");
}

TEST(CategoryTest, At_NoChildren) {
    Category* c1 = new Category("Category One");
    
    ASSERT_EQ(c1->at(0), nullptr);
}

TEST(CategoryTest, At_Children) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello");
    Task* t4 = new Task("world");
    c1->add(t1); c1->add(t2); c1->add(t3); c1->add(t4);

    EXPECT_EQ(c1->getSize(), 4);
    ASSERT_NE(c1->at(0), nullptr);
    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    ASSERT_NE(c1->at(1), nullptr);
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    ASSERT_NE(c1->at(2), nullptr);
    EXPECT_EQ(c1->at(2)->getString(), "hello");
    ASSERT_NE(c1->at(3), nullptr);
    EXPECT_EQ(c1->at(3)->getString(), "world");
}

TEST(CategoryTest, ToggleComplete_All) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello world");
    c1->add(t1); c1->add(t2); c1->add(t3);

    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello world");

    c1->display(); std::cout << std::endl;
    EXPECT_EQ(c1->is_complete(), false);

    c1->toggleComplete();
    c1->display(); std::cout << std::endl;
    EXPECT_EQ(c1->is_complete(), true);

    c1->toggleComplete();
    c1->display(); std::cout << std::endl;
    EXPECT_EQ(c1->is_complete(), false);
}

TEST(CategoryTest, ToggleComplete_OneOff) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello world");
    c1->add(t1); c1->add(t2); c1->add(t3);

    t2->toggleComplete();

    EXPECT_EQ(c1->at(0)->getString(), "lorem");
    EXPECT_EQ(c1->at(1)->getString(), "ipsum");
    EXPECT_EQ(c1->at(2)->getString(), "hello world");
    c1->display(); std::cout << std::endl;
    EXPECT_EQ(c1->is_complete(), false);

    c1->toggleComplete();
    c1->display(); std::cout << std::endl;
    EXPECT_EQ(c1->is_complete(), false);

    c1->toggleComplete();
    c1->display(); std::cout << std::endl;
    EXPECT_EQ(c1->is_complete(), false);
}

TEST(CategoryTest, SetGetString) {
    Category* c1 = new Category("Category One");
    
    std::cout << "Intialize category..." << std::endl;
    c1->display();
    EXPECT_EQ(c1->getString(), "Category One");
    std::cout << std::endl;

    std::cout << "Change category name..." << std::endl;
    c1->setString("Lorem Ipsum");
    c1->display();
    EXPECT_EQ(c1->getString(), "Lorem Ipsum"); 
}

TEST(CategoryTest, Save) {
    Category* c1 = new Category("Category One");
    Task* t1 = new Task("lorem");
    Task* t2 = new Task("ipsum");
    Task* t3 = new Task("hello");
    Task* t4 = new Task("world");
    c1->add(t1); c1->add(t2); c1->add(t3); c1->add(t4);
    t1->toggleComplete();
    t3->toggleComplete();

    Category* c2 = new Category("Category Two");
    Task* t5 = new Task("lorem ipsum");
    Task* t6 = new Task("hello world");
    c2->add(t5); c2->add(t6);
    t6->toggleComplete();

    EXPECT_EQ(c1->getSize(), 4);
    EXPECT_EQ(c2->getSize(), 2);

    c1->display(); c2->display(); // expected info to write into file

    std::ofstream out;
    std::string filename = "category_test.txt";

    out.open(filename); out.close(); // clear file to write to
    
    out.open(filename, std::ios::app);
    c1->save(out);
    c2->save(out);
}

#endif //__CATEGORY_TEST_HPP__
