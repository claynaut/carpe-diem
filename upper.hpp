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
	}
};
#endif //__UPPER_HPP__
