#ifndef __BASEDECORATOR_HPP__
#define __BASEDECORATOR_HPP__

#include "base.hpp"

class BaseDecorator : public Base {
    private:
        Base* x;
    public:
        BaseDecorator(Base* src) { this->x = src; }

        virtual void display() = 0;
};

#endif //__BASEDECORATOR_HPP__

