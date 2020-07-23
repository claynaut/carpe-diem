#ifndef __VISITOR_TEST_HPP__
#define __VISITOR_TEST_HPP__

#include "gtest/gtest.h"

#include "visitor.hpp"
#include "base.hpp"
#include "category.hpp"
#include "task.hpp"
#include "lower.hpp"
#include "upper.hpp"
#include <list>

TEST(VisitorTest, ComboTest1) {
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

	std::cout << "Remove task -1..." << std::endl;
   		c1->remove(-1);
    		c1->display();
    		EXPECT_EQ(c1->getSize(), 3);
    		EXPECT_EQ(c1->at(0)->getString(), "lorem");
    		EXPECT_EQ(c1->at(1)->getString(), "hello");
    		EXPECT_EQ(c1->at(2)->getString(), "world");
    		

	
	t1->toggleComplete();

	EXPECT_EQ(c1->is_complete(), false);

	std::cout << "Change category name..." << std::endl;
   		c1->setString("Test Category");
    		c1->display();
    		EXPECT_EQ(c1->getString(), "Test Category"); 		
//-------------------------------------------------------------
	std::list<Base*>::iterator it;
	Visitor* v = new Visitor();

	c1->accept(v);
    	
//-------------------------------------------------------------
	
	EXPECT_EQ(v->task_count(),3);
	EXPECT_EQ(v->complete_task_count(), 1);
	EXPECT_EQ(v->incomplete_task_count(),2);
	EXPECT_EQ(v->category_count(), 1);    
}

TEST(VisitorTest, ComboTest2) {

	std::cout << "Creating new Category.." << std::endl;

        Category* c1 = new Category("Test One");
        Task* t1 = new Task("laundry");
        Task* t2 = new Task("dishes");
        Task* t3 = new Task("vacuum");
        Task* t4 = new Task("mop");

	c1->add(t1);
        c1->add(t2);
        c1->add(t3);
        c1->add(t4);

	c1->display();

	
	std::cout<< std::endl << "Upper test" << std::endl;
        Base* upper = new Upper(c1);


	upper->display();
       

         std::cout<<std::endl << "Remove task 2..." << std::endl;
                c1->remove(1);
                Base* upper2 = new Upper(c1);;
                EXPECT_EQ(c1->getSize(), 3);
                EXPECT_EQ(c1->at(0)->getString(), "laundry");
                EXPECT_EQ(c1->at(1)->getString(), "vacuum");
                EXPECT_EQ(c1->at(2)->getString(), "mop");
	
	std::cout << std::endl << "Category Completed..." << std::endl;

        upper2->toggleComplete();
  	upper2->display(); 

        EXPECT_EQ(upper2->is_complete(), true);

        std::list<Base*>::iterator it;
        Visitor* v = new Visitor();

        upper->accept(v);

//------------------------------------------------------------- 
        EXPECT_EQ(v->task_count(),3);
        EXPECT_EQ(v->complete_task_count(), 3);
        EXPECT_EQ(v->incomplete_task_count(),0);
        EXPECT_EQ(v->category_count(), 1);

                                
}


TEST(VisitorTest, ComboTest3) {

        std::cout << "Creating new Category.." << std::endl;

        Category* c1 = new Category("Test One");
        Task* t1 = new Task("laundry");
        Task* t2 = new Task("dishes");
        Task* t3 = new Task("vacuum");
        Task* t4 = new Task("mop");

        c1->add(t1);
        c1->add(t2);
        c1->add(t3);
        c1->add(t4);

        c1->display();


        std::cout<< std::endl << "Upper test" << std::endl;
        Base* upper = new Upper(c1);


        upper->display();


         std::cout<<std::endl << "Remove task 2..." << std::endl;
                c1->remove(1);
                Base* upper2 = new Upper(c1);;
                EXPECT_EQ(c1->getSize(), 3);
                EXPECT_EQ(c1->at(0)->getString(), "laundry");
                EXPECT_EQ(c1->at(1)->getString(), "vacuum");
                EXPECT_EQ(c1->at(2)->getString(), "mop");

        std::cout << std::endl << "Category Completed..." << std::endl;

        upper2->toggleComplete();
        upper2->display();

        EXPECT_EQ(upper2->is_complete(), true);

	Base* lower = new Lower(upper2);
	
	std::cout << std::endl << "Back to lower..." << std::endl;
	lower->display();

        std::list<Base*>::iterator it;
        Visitor* v = new Visitor();

        lower->accept(v);

//------------------------------------------------------------- 
	        EXPECT_EQ(v->task_count(),3);
                EXPECT_EQ(v->complete_task_count(), 3);
                EXPECT_EQ(v->incomplete_task_count(),0);
                EXPECT_EQ(v->category_count(), 1);
		EXPECT_EQ(v->upper_count(),1);
		EXPECT_EQ(v->lower_count(),1);
                                }
                                


















#endif
