#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

#include "base.hpp"

class Visitor {
    private:
        int task = 0;
        int completeTask = 0;
        int incompleteTask = 0;
        int category = 0;

    public:
       
	Visitor() {}

        void visitTask() {task++; }
        int task_count() { return task; }
        void visitCompleteTask() {completeTask++;}
        int complete_task_count() { return completeTask; }
        void visitIncompleteTask() {incompleteTask++; }
        int incomplete_task_count() { return incompleteTask; }

        void visitCategory() {category++; }
        int category_count() { return category; }
};

#endif //__VISITOR_HPP__

