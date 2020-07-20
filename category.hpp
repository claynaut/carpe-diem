#ifndef __CATEGORY_HPP__
#define __CATEGORY_HPP__

#include <list>

#include "base.hpp"

class Base;

class Category : public Base {
     private:
         std::string str = "";
         std::list<Base*> children;
     public:
         Category(std::string src) : Base() { this->str = src; }

         void add(Base* src) { children.push_back(src); }
         void remove(int i) {
             if (i <= 0 || i > children.size()) { return; }
             std::list<Base*>::iterator it;
             for (it = children.begin(); it != children.end(); it++) {
                 if (i == 1) {
                     it = children.erase(it);
                 }
                 i--;
             }
         }
         int getSize() { return children.size(); }

         virtual void setString(std::string src) { this->str = src; }
         virtual std::string getString() { return str; }
         virtual void display() {
             std::cout << str << std::endl;
             int count = 1;
             std::list<Base*>::iterator it;
             for (it = children.begin(); it != children.end(); it++) {
                 std::cout << count++ << ". ";
                 (*it)->display();
                 std::cout << std::endl;
             }
         }
         virtual void save(std::ofstream& out, std::string filename) {
             out << ":category: " << str << std::endl;
             std::list<Base*>::iterator it;
             it = children.begin();

             for (it = children.begin(); it != children.end(); it++) {
                 (*it)->save(out, filename);
             }
         }
};

#endif //__CATEGORY_HPP__

