#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <iostream>
#include <string>
#include <fstream>

class Base {
    public:
        Base () { }

        virtual bool is_complete() = 0;
        virtual void toggleComplete() = 0;
        virtual void display() = 0;
        virtual void setString(std::string src) = 0;
        virtual std::string getString() = 0;
        virtual void save(std::ofstream& out, std::string filename) = 0;
};

#endif //__BASE_HPP__

