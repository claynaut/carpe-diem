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
**Problem:** 
We had two objects, `Tasks` and `Categories`, which we wanted to display to console. However, `Categories` can contain multiple `Tasks` and `Categories` which can contain more objects so accessing each individual object to display its information would not be ideal.

**Solution:** We worked with `Tasks` and `Categories` in the same interface to solve this problem. Now, `Categories` can display their information *and* the information of its children, whether it's a `Task` or a `Category`.

**Implementation:**

---

### Decorator Pattern

---

### Visitor Pattern

## Class Diagrams
### Composite Pattern
![alt text](https://github.com/claynaut/final-project-nh-jp-mh/blob/master/images/composite-pattern.png)

---

### Decorator Pattern

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
