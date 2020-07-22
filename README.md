# Carpe Diem 
> A productivity journal app for the day.

### Group member information:
| Name                     | Email            |
| ------------------------ | ---------------- | 
| Naomi Hossain            | nhoss005@ucr.edu |
| Jamella Suzanne Pescasio | jpesc002@ucr.edu |
| Matthew Huang            | mhuan060@ucr.edu |

### What is Carpe Diem?
Carpe Diem is a **productivity journal app** for the day. It aims to keep the user focused on the present by limiting planning to one day.

Carpe Diem allows the user to **create a to-do list** for the day. Anything that has not been completed for the current day will be carried over the next day, though the user has the option to either keep past objectives or delete them.

### Why is it important and interesting?
This app keeps the user focused with what they need to do for the day. Instead of having a weekly planner or a monthly planner, the user is limited to a daily planner so that their focused on *one* thing, seizing the day. 

This app aims to limit procrastination by not allowing the user to plan ahead, only allowing them to focus on what needs to be done that day.

### What language/tools/technology do we plan to use?
Language:
- C++

Tools:
- Vim

### What will be the input/output of our project?
The input will be the objectives the user needs to complete in their to-do list. The output will be a to-do list featuring those objectives under their respective categories.

## Design Pattern Use
### Composite Pattern
**Problem:** We had two objects, `Tasks` and `Categories`, which we wanted to display to console. However, `Categories` can contain multiple `Tasks` and `Categories` which can contain more objects so accessing each individual object to display its information would not be ideal.

**Solution:** We worked with `Tasks` and `Categories` in the same interface to solve this problem. Now, `Categories` can display their information *and* the information of its children, whether it's a `Task` or a `Category`.

**Implementation:**

We used the following abstract base class (found in `base.hpp`) as an interface for `Tasks` and `Categories` to implement this solution.
```cpp
class Base {
    public:
        Base () { }

        virtual Base* at(int i) = 0;
        virtual bool is_complete() = 0;
        virtual void toggleComplete() = 0;
        virtual void display() = 0;
        virtual void setString(std::string src) = 0;
        virtual std::string getString() = 0;
        virtual void save(std::ofstream& out) = 0;
};
```
   
We developed the pure virtual functions with the following objectives.
- `at(int)`: Returns the child at the following index. If the object calling this function is a leaf node, such as a `Task` object, the function returns a `nullptr`.

- `is_complete()`: Returns a boolean value regarding the status of completion. `Tasks` have a private variable that shows their status of completion, with the initial state of `false`. If a `Category` object has children, each child `Task` calls this function and if at least one child returns false the function called by the `Category` object.

- `toggleComplete()`: Toggles the status of completion of the object that calls it. If the object's status of completion was `true`, it will be changed to `false` and vice versa. If the object has children, each child's status of completion will be toggled.

- `display()`: Outputs to console the names of each `Task` and `Category`. If a `Task` object calls the function, a string indicating its completion status will also be outputted ("[x]" for complete and "[ ]" for incomplete). If a `Category` object has children, each child `Task` calls this function and each child will be displayed in a numerical list.

- `setString(std::string)`: Modifies the name of the object calling it.

- `getString()`: Returns the name of the object calling it.

- `save(std::ofstream)`: Writes to file a tag which indicates the object's class (":task:" for `Task` and ":category:" for `Category`) and the object's name. If a `Task` object calls this function, an additional string is written to file which indicates the status of completion ("+" for complete and "-" for incomplete). If a `Category` object has children, each child `Task` calls this function.

We then developed the classes `Task` and `Category` which we needed to implement this design pattern.
- Class `Task`: This class represents the tasks in a to-do list and is the leaf node in a composite pattern. It has two private variables, a string representing its name and a boolean value representing its status of completion.

- Class `Category`: This class reprents the categories in a to-do list and is the composite/container in a composite pattern. It has two private variables, a string representing its name and a list of `Base*` objects representing its children, whether it's a `Task` object or another `Category` object. 

   This class also contains three additional functions to aid in its functionality of adding, removing, and accessing its children.

    - `add(Base*)`: Adds a `Base*` object to the `Category` object's list of children.
    
    - `remove(int)`: Removes a child in the `Category` object's list of children at the specified index.
    
    - `getSize()`: Returns the size of the `Category` object's list of children.

---

### Decorator Pattern
**Problem:** We wanted the user to be able to change the text to either be all in lowercase or all in uppercase depending on their preference at any given time. However, we needed it to be able to change `Categories` and `Task` objects without affecting their behavior at run-time. 

**Solution:** We decided to extend the interface, implementing a `Lower` and `Upper` class dynamically in order for the user to be able to decide whether they want to change the text to all lowercase or all uppercase.

---

### Visitor Pattern

## Class Diagrams
### Composite Pattern
![alt text](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/composite-pattern.png)

---

### Decorator Pattern
![alt text](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/Decorator-Pattern-Diagram.png)

---

### Visitor Pattern

## Input/Output


## How To Run the Code
> This app runs in a terminal, so the following lines of code will be done in command line.

Clone the repository:
```
$ git clone https://github.com/claynaut/final-project-nh-jp-mh.git
```
Compile the code (use `cmake3 .` if on `hammer`):
```
$ cmake .
$ make
```
Run the executable:
```
$ ./carpe_diem
```
