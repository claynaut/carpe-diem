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
        Lower(Base* x) : BaseDecorator(x) { }

        void display() { 
		/*char* str[] = x->getString();
		for (int i = 0; i < str.size(); i++) {
                        //putchar(tolower(str[i]));
			std::cout << std::putchar(tolower(x[i])) << std::endl; 
                }*/
		int j = 0;
		std::string str = x->getString();
		//char* str = x->getString();
		char ch = str[0];
		while (str[j]) {
			ch = str[j];
			putchar(tolower(ch));
			j++;
		}
	}
};

#endif //__LOWER_HPP__

