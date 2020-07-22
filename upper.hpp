#ifndef __UPPER_HPP__
#define __UPPER_HPP__

#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "baseDecorator.hpp"

class Upper : public BaseDecorator {
    private:
        Base* x;
    public:
        Upper(Base* x) : BaseDecorator(x) { this->x = x;}

        void display() {
                int j = 0;
                std::string str = x->getString();
                char ch = str[0];
                while (str[j]) {
                        ch = str[j];
                        putchar(toupper(ch));
                        j++;
                }
                std::cout << std::endl;
	
		int i = 0;
                while (x->at(i)) {
                        std::cout << i + 1 << ". ";
                        if (x->at(i)->is_complete()) {
                                std::cout << "[x] ";
                        }
                        else {
                                std::cout << "[ ] ";
                        }
                        j = 0;
                        str = x->at(i)->getString();
                        ch = str[0];
                        while (str[j]) {
                                ch = str[j];
                                putchar(toupper(ch));
                                j++;
                        }
                        i++;
                        std::cout << std::endl;
                }
	}

	void accept(Visitor* v) { x->accept(v); v->visitUpper(); }
};
#endif //__UPPER_HPP__
