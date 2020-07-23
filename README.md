# Carpe Diem 
> A productivity journal app for the day.

### Group member information:
| Name                     | Email            |
| ------------------------ | ---------------- | 
| Naomi Hossain            | nhoss005@ucr.edu |
| Jamella Suzanne Pescasio | jpesc002@ucr.edu |
| Matthew Huang            | mhuan060@ucr.edu |

### What is Carpe Diem?
Carpe Diem is a **productivity journal app** for the day. It aims to keep the user focused on the present by limiting planning to one day and three categories, high priority, medium priority, and low priority.

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
- **Class** `Task`: This class represents the tasks in a to-do list and is the leaf node in a composite pattern. It has two private variables, a string representing its name and a boolean value representing its status of completion.

- **Class** `Category`: This class reprents the categories in a to-do list and is the composite/container in a composite pattern. It has two private variables, a string representing its name and a list of `Base*` objects representing its children, whether it's a `Task` object or another `Category` object. 

   This class also contains three additional functions to aid in its functionality of adding, removing, and accessing its children.

    - `add(Base*)`: Adds a `Base*` object to the `Category` object's list of children.
    
    - `remove(int)`: Removes a child in the `Category` object's list of children at the specified index.
    
    - `getSize()`: Returns the size of the `Category` object's list of children.

---

### Decorator Pattern
**Problem:** We wanted the user to be able to change the text to either be all in lowercase or all in uppercase depending on their preference at any given time. However, we needed it to be able to change `Categories` and `Task` objects without affecting their behavior at run-time. 

**Solution:** We decided to extend the interface, implementing a `Lower` and `Upper` class dynamically in order for the user to be able to decide whether they want to change the text to all lowercase or all uppercase.

**Implementation:**

We used the following abstract base decorator class (`baseDecorator.hpp`) which inherits from `base.hpp`. The baseDecorator is an interface for the `Lower` and `Upper` classes. 

```cpp
class BaseDecorator : public Base {
    private:
        Base* x;
    public:
        BaseDecorator(Base* src) { this->x = src; }
	
        virtual Base* at(int i) { return x->at(i); }
        virtual bool is_complete() { return x->is_complete(); }
        virtual void toggleComplete() { x->toggleComplete(); }
        virtual void display() { x->display(); }
	virtual void setString(std::string src) { x->setString(src); }
	virtual std::string getString() { return x->getString(); } 
	virtual void save(std::ofstream& out) { x->save(out); }
};
```

The `baseDecorator` class inherits all the pure virtual functions from the `base.hpp` class. We implemented two new classes that inherit from the `baseDecorator` class:
- **Class** `Lower`: This class will output a given string where all characters are in lowercase. It contains a private `Base*` variable and a display function. 

- **Class** `Upper`: This class will output a given string where all characters are in uppercase. It contains a private `Base*` variable and a display function.

    - `display()`: Both classes implement a display function inherited from the `baseDecorator.hpp` class. The function creates a copy of the string and converts all the characters into the desired style. 

---

### Visitor Pattern
**Problem:** Our project is essentially an online journal. We wanted the user to be able to keep track of each `Task`, `Category`, and their behavior without necessarily changing their structure.

**Solution:** We decided to introduce a Visitor class. By having a specific function, `visit()`, called onto each element in the data structure, we can track each element without altering its structure.

**Implementation:**

We implemented our own `Visitor` class with the following private/public variables that solved our problem. 

```cpp
class Visitor {
    private:
        int task = 0;
        int completeTask = 0;
        int incompleteTask = 0;
        int category = 0;
   	int lower = 0;
	int upper = 0;

    public:
       
	Visitor() {}

        void visitTask() { task++; }
        int task_count() { return task; }
        void visitCompleteTask() {completeTask++;}
        int complete_task_count() { return completeTask; }
        void visitIncompleteTask() { incompleteTask++; }
        int incomplete_task_count() { return incompleteTask; }

        void visitCategory() { category++; }
        int category_count() { return category; }

	void visitLower() { lower++; }
 	int lower_count() { return lower;}
	void visitUpper() { upper++; }
	int upper_count() { return upper; }
};
```

- **Class** `Visitor`: This class will visit each element and return a number based on the the total amount present in the data structure. 
	- Private Member Variables: The declaration of these specific variables are the ones the user would want to keep track of.
	- Public Variables: The `Visitor` class calls a function to visit each element, increment (if applicable), and return it’s value. 

## Class Diagrams
### Composite Pattern
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/composite-pattern.png)

---

### Decorator Pattern
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/Decorator-Pattern-UML-Diagram.png)

---

### Visitor Pattern

## Input/Output
### Home Menu
> After running the app, the following menu is printed in console. Upon initial set-up, the to-do list is blank.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/home-menu-1.PNG)

From this menu, the user has seven options to choose from:
- **Input** `a`: Prompts the user to add a task in a specified category.

- **Input** `r`: Prompts the user to remove a task in a specified category.

- **Input** `e`: Prompts the user to edit a task in a specified category.

- **Input** `x`: Prompts the user to toggle a task as complete/incomplete in a specified category.

- **Input** `c`: Clears completed tasks from the to-do list.

- **Input** `s`: Outputs the current display settings to console and prompts the user with the option to change the display settings.

- **Input** `q`: Ends the program and saves any changes made to the to-do list and settings by writing them into a file specified by the program.

### Add Task - Input `a`
> After inputting `a`, the program prompts the user to choose which category to add a task to.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/add-task-1.PNG)

> After specifying the category, the program prompts the user to type the name of the task. 

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/add-task-2.PNG)

> After entering the name, a new task is created and displayed in the home menu.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/add-task-3.PNG)

### Remove Task - Input `r`
> After inputting `r`, the program prompts the user to choose which category to remove a task from.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/remove-task-1.PNG)

> After specifying the category, the program prompts the user to choose which task to remove. 

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/remove-task-2.PNG)

> After selecting a task, the task is removed and is no longer displayed in the home menu.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/remove-task-3.PNG)

### Edit Task - Input `e`
> After inputting `e`, the program prompts the user to choose which category to choose a task to edit.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/edit-task-1.PNG)

> After specifying the category, the program prompts the user to choose which to edit. 

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/edit-task-2.PNG)

> After selecting a task, the program prompts the user to type a new name for the task. 

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/edit-task-3.png)

> After entering the new name, the new name overwrites the previous name and will now be displayed in the home menu.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/edit-task-4.PNG)

### Toggle Complete/Incomplete - Input `x`
> After inputting `x`, the program prompts the user choose which category to choose a task to toggle as complete/incomplete.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/toggle-1.PNG)

> After specifying the category, the program prompts the user to choose which task to toggle as complete/incomplete. 

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/toggle-2.PNG)

> After selecting a task, the task is toggled as complete/incomplete and will be displayed as that in the home menu.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/toggle-3.PNG)

### Clear Complete - Input `c`
> After inputting `c`, the program clears completed tasks from the to-do list.

Initial state:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/clear-1.PNG)

Output:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/clear-2.PNG)

### Settings - Input `s`
> After inputting `s`, the program outputs the current display settings to console and prompts the user with the option to change the display settings.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/settings-1.PNG)

> If the user chooses to change the display settings (inputting `y` or `Y`), the program prompts the user to choose which setting to change to.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/settings-2.PNG)

> After choosing which setting to change to, the setting is saved and the category names and task names will be displayed as specified in the settings.

Selecting lowercase:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/settings-2a.PNG)

Selecting uppercase:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/settings-2b.PNG)

Selecting default:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/settings-2c.PNG)

> Otherwise, if the user chooses to not make any changes to the display settings, the program returns to the home menu.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/settings-3.PNG)

### Quit - Input `q`
> After inputting `q`, the program ends itself and saves any changes made to the to-do list and settings by writing them into a file specified by the program. The save file is currently set to be labeled as `carpediem_savefile.txt`.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/quit.PNG)

### Loading Save Files
> If the user had run the program beforehand and a save file was successfully generated, the program will load that save file if the current date matches the save file's date of creation. Otherwise, the program gives the user the option to either carry over the incomplete tasks from the save file or create a new to-do list. 

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/save-1.PNG)

> If the user chooses to carry over the incomplete tasks from the save file (inputting `y` or `Y`), the incomplete tasks will be loaded into the program.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/save-2.png)

> But if the user chooses to not carry over the incomplete tasks from the save file (inputting `n` or `N`), a blank to-do list will be generated.

![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/save-3.png)

### Invalid Inputs
> Input validation exists when choosing an option in the home menu, choosing a category, choosing a task, choosing a setting, and answering Y/N prompts. An error message will be printed to console and the user will be given another chance to input until the input is valid.

Choosing an invalid option in the home menu:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/menu-error-1.PNG)
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/menu-error-2.PNG)
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/menu-error-3.PNG)

Choosing an invalid category:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/category-error-1.PNG)

Choosing an empty category:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/empty.PNG)

Choosing an invalid task:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/task-error-1.PNG)

Choosing an invalid setting:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/setting-error-1.PNG)

Answering the `Y/N` prompt for loading a save file with invalid input:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/yn-prompt-1.PNG)

Answering the `Y/N` prompt for changing a setting with invalid input:
![](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/yn-prompt-2.PNG)

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
