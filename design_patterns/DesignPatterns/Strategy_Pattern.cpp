class Engine {
    public:
        virtual void move() = 0;
}; // Engine Interface

class CombustionEngine: public Engine {
    public:
        void move() {
            // ... brum!
        }
}; // CombustionEngine is Concrete class

class ElectricEngine: public Engine {
    public:
        void move() {
            // ... zing!
        }
}; // ElectricEngine is Concrete class

class Driver {
    public:
        virtual void navigate() = 0;
}; // Driver Interface

class Robot: public Driver {
    public:
        void navigate() {
            // ...
        }
}; // Robot is Concrete class

class Human: public Driver {
    public:
        void navigate() {
            // ...
        }
}; // Human is Concrete class

class Transport {
    private:
        Engine* engine;
        Driver* driver;
    public:
        Transport(Driver* d) {
            engine = new CombustionEngine(); // Composition , Engine's dies when Transport dies
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
