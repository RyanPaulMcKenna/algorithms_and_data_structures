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