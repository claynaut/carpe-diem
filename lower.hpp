#ifndef __LOWER_HPP__
#define __LOWER_HPP__

#include <cctype>
#include “baseDecorator.hpp”

class Lower : public BaseDecorator {
    private:
        Base* x;
    public:
        Lower() : BaseDecorator(Base* src) { }

        virtual void display() { 
		x.getString();
	       	for (int i = 0; i < strlen(x); i++) {
                        //putchar(tolower(x[i]));
			std::cout << std::putchar(tolower(x[i])) << std::endl; 
                }
	}
};

#endif //__LOWER_HPP__

