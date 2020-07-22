#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <iostream>
#include <string>
#include <fstream>

#include "visitor.hpp"

class Base {
    public:
        Base () { }

        virtual Base* at(int i) = 0;
        virtual bool is_complete() = 0;
        virtual void toggleComplete() = 0;
        virtual void display() = 0;
        virtual void setString(std::string src) = 0;
        virtual std::string getString() = 0;
        virtual void save(std::ofstream& out, std::string filename) = 0;
	virtual void accept(Visitor*) = 0;
};


#endif //__BASE_HPP__

