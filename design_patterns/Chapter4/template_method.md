# TEMPLATE METHOD

**Template Method** is a behavioral design pattern that defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

# The Problem
Imagine you are building a data mining application that needs to work with several different file types, cvs, doc, pdf, etc.
The miner is doing the same thing with every file type; extrating the information and analysing the date. The extration is very different for each file type whereas the rest of the code is identical.

# The Solution
**The Template Method** pattern suggests that you break down an algorith intoa series of steps, turn these steps into methods, and put a series of calls to the these methods inside a single *template method*. 

These steps come in three types:

* *abstract steps* must be implemented by every subclass
* *optional steps* already have some default implementation, but still can be overriden if needed
* *hooks* (optional steps with an empty body)

![template method](/chapter4/diagrams/template_method.png)

# C++ Implementation: Game AI

```c++
#include <iostream>
#include <utility>

// ABSTRACT CLASS
class GameAI {
    private:
    //...
    public:
        virtual void takeTurn() = 0;
        virtual void collectResources() = 0;
        virtual void buildStructures() = 0;
        virtual void buildUnits() = 0;
        virtual void attack() = 0;
        virtual void sendScouts(std::pair<int, int> pos) = 0;
        virtual void sendWarriors(std::pair<int, int> pos)  = 0;
};

// CONCRETE CLASSES
class OrcsAI: public GameAI { 
    private:
        void takeTurn() {
            std::cout << "Orcs take turn" << std::endl;
        }
        void collectResources() {
            std::cout << "Orcs collect resources" << std::endl;
        }
        void buildStructures() {
            std::cout << "Orcs build structures" << std::endl;
        }
        void buildUnits() {
            std::cout << "Orcs build units" << std::endl;
        }
        void attack() {
            std::cout << "Orcs attack" << std::endl;
        }
        void sendScouts(std::pair<int, int> pos) {
            std::cout << "Orcs send scouts to: " << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
        void sendWarriors(std::pair<int, int> pos) {
            std::cout << "Orcs send warriors to "  << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
};

class MonstersAI : public GameAI {
    private:
        void takeTurn() {
            std::cout << "Monsters take turn" << std::endl;
        }
        void collectResources() {
            std::cout << "Monsters collect resources" << std::endl;
        }
        void buildStructures() {
            std::cout << "Monsters cannot build structures" << std::endl;
        }
        void buildUnits() {
            std::cout << "Monsters cannot build units" << std::endl;
        }
        void attack() {
            std::cout << "Monsters attack" << std::endl;
        }
        void sendScouts(std::pair<int, int> pos) {
            std::cout << "Monsters send scouts to: " << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
        void sendWarriors(std::pair<int, int> pos) {
            std::cout << "Monsters send warriors to " << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
};

int main() {
    GameAI* orcs = new OrcsAI();
    GameAI* monsters = new MonstersAI();

    std::cout << "Orcs" << std::endl;
    orcs->takeTurn();
    orcs->collectResources();
    orcs->buildStructures();
    orcs->buildUnits();
    orcs->attack();
    orcs->sendScouts(std::make_pair(1, 2));
    orcs->sendWarriors(std::make_pair(3, 4));

    std::cout << "Monsters" << std::endl;
    monsters->takeTurn();
    monsters->collectResources();
    monsters->buildStructures();
    monsters->buildUnits();
    monsters->attack();
    monsters->sendScouts(std::make_pair(5, 6));
    monsters->sendWarriors(std::make_pair(7, 8));
    return 0;
}
```

*AI classes of a simple video game.*

# Applicability 
Use the **Template Method** pattern when you want to let clients extend only particular steps of an algorithm but not the whole algorithm or its structure.

The **Template Method** lets you turn a monolithic algorithm into a series of individual steps which can easily be extended by subclasses while keeping intaact the strcuture definedin a superclass.

# Pros and Cons

* ::heavy_check_mark: You can let clients override only certain parts of a large algorithm, making them less affected by changes that happen to other parts of the algorithm.
* :heavy_check_mark: You can pull duplicate code into a superclass.
* :x: Templates methods tend to be harder to maintain the more steps they have.
* :x: Might violate the *Liskov Substitution Principle* by suppressing a default step implementation via a subclass.
 
