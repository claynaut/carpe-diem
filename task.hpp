#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "base.hpp"

class Task : public Base {
    private:
        std::string str = "";
        bool complete = false;
    public:
        Task(std::string src) : Base () { this->str = src; }

        virtual Base* at(int i) { return nullptr; }
        virtual bool is_complete() { return complete; }
        virtual void toggleComplete() { 
            if (complete) {
                complete = false;
            }
            else {
                complete = true;
            }
        }
        
        virtual void display() { 
            if (complete) {
                std::cout << "[x] ";  
            }
            else {
                std::cout << "[ ] ";
            }
            std::cout << str; 
        }
        virtual void setString(std::string src) { this->str = src; }
        virtual std::string getString() { return str; }
        virtual void save(std::ofstream& out, std::string filename) {
            out << ":task: ";
            if (complete) {
                out << "[x] ";
            }
            else {
                out << "[ ] ";
            }
            out << str << std::endl;
        }

	virtual void accept(Visitor* v) { 
	
	if(complete == false) {
		v->visitIncompleteTask();
	}
	else {
		v->visitCompleteTask();
	}	
		v->visitTask();
	}
};

#endif //__TASK_HPP__

