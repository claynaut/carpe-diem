#ifndef __BASEDECORATOR_HPP__
#define __BASEDECORATOR_HPP__

#include "base.hpp"

class BaseDecorator : public Base {
    private:
        Base* x;
    public:
        BaseDecorator(Base* src) { this->x = src; }
	
        virtual void display() { x->display(); }
	virtual void setString(std::string src) { x->setString(src); }
	virtual std::string getString() { return x->getString(); } 
	virtual void save(std::ofstream& out, std::string filename) { x->save(out, filename); }
};

#endif //__BASEDECORATOR_HPP__

