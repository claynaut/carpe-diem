#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>

#include "task.hpp"
#include "category.hpp"
#include "lower.hpp"
#include "upper.hpp"
#include "visitor.hpp"

Category* chooseCategory(const std::vector<Category*>&);
int chooseTask(Category*);
void displayList(const std::vector<Base*>&);
void addTask(std::vector<Category*>&);
void removeTask(std::vector<Category*>&);
void editTask(std::vector<Category*>&);
void toggleTaskCompletion(std::vector<Category*>&);
void clearCompleteTasks(std::vector<Category*>&);
void editSettings(int&);
std::string getTimeStamp();
void saveToFile(std::ofstream&, std::string, const int&, const std::vector<Category*>&);
void parseSaveFile(std::ifstream&, std::string, std::string&, int&, std::vector<Category*>&);

int main() {
    std::string filename = "carpediem_savefile.txt";
    std::string time = getTimeStamp();
    int setting = 1;
    Category* high = new Category("High Priority");
    Category* med = new Category("Medium Priority");
    Category* low = new Category("Low Priority");

    std::vector<Category*> categories;

    std::vector<Category*> initialSet;
    initialSet.push_back(high);
    initialSet.push_back(med);
    initialSet.push_back(low);

    std::vector<Category*> savedSet;

    std::ifstream in(filename);
    if (in.is_open()) { 
	std::cout << "Save file found..." << std::endl;
	parseSaveFile(in, filename, time, setting, savedSet); 
        categories = savedSet;
        std::cout << "Save file loaded..." << std::endl << std::endl;
    }
    else {
	categories = initialSet;
    }
    in.close();
    
    if (time != getTimeStamp()) {
	std::cout << "A day has passed since you last made your journal." << std:: endl << std::endl
                  << "Carry over incomplete tasks from the other day? [Y/N] ";

    	std::string input;
    	std::cin >> input;

    	while (input != "y" && input != "Y" && input != "n" && input != "N") {
            std::cout << std::endl << "Invalid input. Try again." << std::endl << std::endl;
            std::cout << "Carry over incomplete tasks from the other day? [Y/N] ";
            std::cin >> input;
    	}

        if (input == "y" || input == "Y") {
	    clearCompleteTasks(savedSet);
            categories = savedSet;
	    std::cout << std::endl << "Previous tasks loaded...";
        }
        else {
            categories = initialSet;
	    std::cout << std::endl << "Previous tasks cleared...";
        }
	std::cout << std::endl << std::endl;
    }

    std::vector<Base*> displaySet;
    displaySet.push_back(categories.at(0));
    displaySet.push_back(categories.at(1));
    displaySet.push_back(categories.at(2));

    std::vector<Base*> defaultSet;
    defaultSet.push_back(categories.at(0));
    defaultSet.push_back(categories.at(1));
    defaultSet.push_back(categories.at(2));

    std::vector<Base*> lowerSet;
    lowerSet.push_back(new Lower(categories.at(0)));
    lowerSet.push_back(new Lower(categories.at(1)));
    lowerSet.push_back(new Lower(categories.at(2)));

    std::vector<Base*> upperSet;
    upperSet.push_back(new Upper(categories.at(0)));
    upperSet.push_back(new Upper(categories.at(1)));
    upperSet.push_back(new Upper(categories.at(2)));
    
    std::string input = "";
   
    while (input != "q") {
        std::cout << "-----------------------------------------------[ CARPE DIEM ]-----------------------------------------------" 
                  << std::endl;

        if (setting == 1) {
            displaySet = defaultSet;
        }
        else if (setting == 2) {
            displaySet = lowerSet;
        }
        else {
            displaySet = upperSet;
        }

        displayList(displaySet);

        std::cout << "------------------------------------------------------------------------------------------------------------" 
                  << std::endl
                  << "| a: add | r: remove | e: edit | x: toggle complete/incomplete | c: clear complete | s: settings | q: quit |" 
                  << std::endl << std::endl;

        std::cout << "Choose an option: ";
        std::cin >> input;
        std::cout << std::endl;

        if (input == "a" || input == "A") {
            addTask(categories);
        }
        else if (input == "r" || input == "R") {
            removeTask(categories);
        }
        else if (input == "e" || input == "E") {
            editTask(categories);
        }
        else if (input == "x" || input == "X") {
            toggleTaskCompletion(categories);
        }
        else if (input == "c" || input == "C") {
            clearCompleteTasks(categories);
        }
        else if (input == "s" || input == "S") {
            editSettings(setting);
        }
        else if (input == "q" || input == "Q") {
            break;
        }
        else {
            std::cout << "Invalid input. Try again." << std::endl << std::endl;
        }
    }

    std::ofstream out(filename);
    saveToFile(out, filename, setting, categories);
    out.close();

    std::cout << "Changes saved." << std::endl;

    return 0;
}

Category* chooseCategory(const std::vector<Category*>& c) {
    std::cout << "Which category?" << std::endl << std::endl;
    for (int i = 0; i < c.size(); i++) {
        Base* curr = c.at(i);
        std::cout << i + 1 << ". " << curr->getString() << std::endl;
    }

    std::cout << std::endl << "Input category number: ";
    std::cin.ignore();
    std::string line;
    int n;
    
    while (std::getline(std::cin, line)) {
        std::cout << std::endl;
        std::stringstream ss(line);
        if (ss >> n) {
            n--;
            if (ss.eof() && n >= 0 && n < c.size()) { 
                break; 
            }
        }
        std::cout << "Invalid input. Try again." << std::endl;
        std::cout << std::endl << "Input category number: ";
    }
    
    return c.at(n);
} 

int chooseTask(Category* c) {
    c->display();
    std::cout << std::endl << "Input task number: ";
    std::string line;
    int n;
      
    while (std::getline(std::cin, line)) {
        std::cout << std::endl;
        std::stringstream ss(line);
        if (ss >> n) {
            n--;
            if (ss.eof() && c->at(n)) {
                break;
            }
        }
        std::cout << "Invalid input. Try again." << std::endl;
        std::cout << std::endl << "Input task number: ";
    }
    
    return n;
}

void displayList(const std::vector<Base*>& c) {
    for (int i = 0; i < c.size(); i++) {
        Visitor* v = new Visitor();
        Base* curr = c.at(i);
        curr->display();
        std::cout << std::endl;
        curr->accept(v);
        std::cout << "[ " << v->task_count() << " Tasks | "
                          << v->complete_task_count() << " Complete | "
                          << v->incomplete_task_count() << " Incomplete] "
                          << std::endl << std::endl;
    }
}

void addTask(std::vector<Category*>& c) {
    Category* curr = chooseCategory(c);

    std::cout << "Input task name: ";
    std::string taskName;
    std::getline(std::cin, taskName);
    std::cout << std::endl;
   
    Base* t = new Task(taskName);
    curr->add(t);
}

void removeTask(std::vector<Category*>& c) {
    Category* curr = chooseCategory(c);

    if (curr->getSize() == 0) {
        std::cout << "Category has no tasks. Choose a different option." << std::endl << std::endl;
        return;
    }

    std::cout << "Remove which task?" << std::endl << std::endl;
    
    int n = chooseTask(curr);
    curr->remove(n);
}

void editTask(std::vector<Category*>& c) {
    Category* curr = chooseCategory(c);

    if (curr->getSize() == 0) {
        std::cout << "Category has no tasks. Choose a different option." << std::endl << std::endl;
        return;
    }

    std::cout << "Edit which task?" << std::endl << std::endl;

    int n = chooseTask(curr);

    std::cout << "New task name: ";
    std::string taskName;
    std::getline(std::cin, taskName);
    std::cout << std::endl;

    curr->at(n)->setString(taskName);
}

void toggleTaskCompletion(std::vector<Category*>& c) {
    Category* curr = chooseCategory(c);

    if (curr->getSize() == 0) {
        std::cout << "Category has no tasks. Choose a different option." << std::endl << std::endl;
        return;
    }

    std::cout << "Toggle which task?" << std::endl << std::endl;

    int n = chooseTask(curr);

    curr->at(n)->toggleComplete();
}

void clearCompleteTasks(std::vector<Category*>& c) {
    for (int i = 0; i < c.size(); i++) {
        Category* curr = c.at(i);
        for (int j = curr->getSize() - 1; j >= 0; j--) {
            if (curr->at(j)->is_complete()) { 
                curr->remove(j);
            }
        }
    }
}

void editSettings(int& setting) {
    std::vector<std::string> temp = {"Default (categories capitalized, tasks user-set case)",
                                     "Lowercase (categories and tasks all lowercase)",
                                     "Uppercase (categories and tasks all uppercase)"};

    std::cout << "Current display settings: " << std::endl;
    for (int i = 0; i < temp.size(); i++) {
        if (i + 1 == setting) {
            std::cout << "[x] ";
        }
        else {
            std::cout << "[ ] ";
        }
        std::cout << temp.at(i) << std::endl;
    }

    std::cout << std::endl << "Change display settings? [Y/N] ";
    std::string input;
    std::cin >> input;
 
    while (input != "y" && input != "Y" && input != "n" && input != "N") {
        std::cout << std::endl << "Invalid input. Try again." << std::endl << std::endl;
        std::cout << "Change display settings? [Y/N] ";
        std::cin >> input;
    }

    std::cout << std::endl;

    if (input == "n" || input == "N") { return; }

    std::cout << "Toggle which setting?" << std::endl << std::endl;
    for (int i = 0; i < temp.size(); i++) {
        std::cout << i + 1 << ". " << temp.at(i) << std::endl;
    }

    std::cout << std::endl << "Input setting number: ";
    std::cin.ignore();
    int n;

    while (std::getline(std::cin, input)) {  
        std::cout << std::endl;
        std::stringstream ss(input);
        if (ss >> n) {    
            if (ss.eof() && n > 0 && n <= temp.size()) { 
                break;
            } 
        }
        std::cout << "Invalid input. Try again." << std::endl;
        std::cout << std::endl << "Input setting number: ";
    }

    setting = n;
    std::cout << std::endl << "Settings saved." << std::endl << std::endl;
}

std::string getTimeStamp() {
    time_t save_time;
    time(&save_time);
    std::string time = std::ctime(&save_time);
    time = time.substr(0, 10);
    return time;
}

void saveToFile(std::ofstream& out, std::string filename, const int& setting, const std::vector<Category*>& c) {
    std::string time = getTimeStamp();
    out << ":time: " << time << std::endl;

    out << ":display: " << setting << std::endl;

    for (int i = 0; i < c.size(); i++) {
        c.at(i)->save(out, filename);
    } 
}

void parseSaveFile(std::ifstream& in, std::string filename, std::string& time, int& setting, std::vector<Category*>& c) {
    if (!in.is_open()) { return; }
    std::string tag = "";
    Category* curr = nullptr;
    std::string currName = "";
    std::string completionStatus = "";

    while (in >> tag) {
        if (tag == ":time:") {
	    in.ignore();
            std::getline(in, time);
        }
        else if (tag == ":display:") {
            in >> setting;
        }
	else if (tag == ":category:") {
            in.ignore();
            std::getline(in, currName);
            curr = new Category(currName);
            c.push_back(curr);
        }
        else if (tag == ":task:") {
            in >> completionStatus;
            in.ignore();
            getline(in, currName);
            Task* t = new Task(currName);
            if (completionStatus == "+") {
	        t->toggleComplete();
            }
            curr->add(t);
        }
    }
}
