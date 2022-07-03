# STRATEGY

**Strategy** is a behavioral design pattern that lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.

# The Problem
You need to something specfic in many different ways. For example a mapping app that builds different types of routes through the city. Cycling routes, walking routes, car routes, fastest routes, scencic routes, tourist attraction routes, etc. There are too many and the becomes bloated and hard to change without introducing bugs or breaking something.

# The Solution
The ***Strategy** pattern suggests that you taks class that does something specific (Navigation) in a lot of different ways and extract all of these algorithms (routes) into seprate classes callled *strategies*.

# Structure

![strategy pattern](/chapter4/diagrams/strategy.png)

*Route planning strategies.*

#### The Pattern is always made up of these building blocks:
* Navigator is the ***Context***
* RoadStrategy is the ***Strategy Interface***
* RoadStrategy, WalkingStrategy, Public TransportStrategy are the ***Concrete Strategies***

# C++ Implementation: Human and Robot drivers driving, Combustion and Electric Vehciles

```c++
#include <iostream>

class Engine {
    public:
        virtual void move() = 0;
}; // Engine Interface

class CombustionEngine: public Engine {
    public:
        void move() {
            std::cout << "Combustion Engine: Brum brum! ";
        }
}; // CombustionEngine is Concrete class

class ElectricEngine: public Engine {
    public:
        void move() {
            std::cout << "Electric Engine: Zing! ";
        }
}; // ElectricEngine is Concrete class

class Driver {
    public:
        virtual void navigate() = 0;
}; // Driver Interface

class Robot: public Driver {
    public:
        void navigate() {
           std::cout << "ROBOT: Navigating protcol initiated!" << std::endl;
        }
}; // Robot is Concrete class

class Human: public Driver {
    public:
        void navigate() {
            std::cout << "HUMAN: And so the journey begins!" << std::endl;
        }
}; // Human is Concrete class

class Transport {
    private:
        Engine* engine;
        Driver* driver;
    public:
        Transport(Driver* d, Engine* e) {
            engine = e;
            driver = d; // Aggregation, driver does not die when Transport dies
        }
        ~Transport() {
            delete engine; // Delete engine
            engine = nullptr;
            driver = nullptr;
        }
        void deliver() {
            engine->move();
            driver->navigate();
        }
};

/*
Strategy Pattern, 
Is a design pattern that enables an algorithm's behavior to be selected at runtime.
Prevents the need for complex inheritance hierarchies. Different "dimensions" of functionality
are extracted into own class hierarchies.
*/
int main() {
    Driver* driver = new Robot();
    Engine* engine = new CombustionEngine();
    Transport* transport = new Transport(driver, engine);
    transport->deliver();
    delete transport;
    delete driver;
    driver = new Human();
    engine = new ElectricEngine();
    transport = new Transport(driver, engine);
    transport->deliver();
}
```

# Applicability

Use the Strategy pattern when you want to use different variants of an algorithm within an object and be able to switch from one algorithm to another during runtime.

The Strategy pattern lets you indirectly alter the object's behavior at runtime by associating it with different sub-objects which can perform specific sub-tasks in different ways.

Use when you have a lot of similar classes that only different in the way they execute some behavior.

# Pros and Cons

* :heavy_check_mark: You can swap algorithms used inside an object at runtime.
* :heavy_check_mark: You can isolate the implementation details of algorithm from the code that uses it.
* :heavy_check_mark: You can replace inheritance with composition.
* :heavy_check_mark: *Open/closed Principle* You can introduce new strategies with-out having to change the context.
