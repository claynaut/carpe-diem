#ifndef __LOWER_HPP__
#define __LOWER_HPP__

#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "baseDecorator.hpp"

class Lower : public BaseDecorator {
    private:
        Base* x;
    public:
        Lower(Base* x) : BaseDecorator(x) { this->x = x;}

        void display() {
		int j = 0;
		std::string str = x->getString();
		char ch = str[0];
		while (str[j]) {
			ch = str[j];
			putchar(tolower(ch));
			j++;
		}
		std::cout << std::endl;
	}
	
};

#endif //__LOWER_HPP__
