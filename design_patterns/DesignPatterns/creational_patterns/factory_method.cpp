#include <vector>

// Exmaple 1
class Employee {
    public:
        virtual void doWork() = 0;
}; // Employee is an Interface, note has no fields.

class Designer: public Employee {
    public:
        void doWork() {
            // Designing...
        }
}; // Designer is a Concrete Class

class Programmer: public Employee {
    public:
        void doWork() {
            // Programming...
        }
}; // Programmer is a Concrete Class

class Tester: public Employee {
    public:
        void doWork() {
            // Testing...
        }
}; // Tester is a Concrete Class

class Artist: public Employee {
    public:
        void doWork() {
            // Artist...
        }
}; // Artist is a Concrete Class

class Company {
    private:
    // .. fields
    public:
    virtual std::vector<Employee*> getEmployees() = 0; // Pure virtual
    virtual void CreateSoftware() = 0;
}; // Company is Abstract class

class GameDevCompany: public Company {
    private:
    // .. fields
    public:
    std::vector<Employee*> getEmployees() {
        // ..
    }
    void CreateSoftware() {
        // ..
    }
}; // GameDevCompany is Concrete

class OutsourcingCompany: public Company {
    private:
    // .. fields
    public:
    std::vector<Employee*> getEmployees() {
        // ...
        std::vector<Employee*> employees = {
            new Designer(),
            new Programmer(),
            new Tester()
        };
        return employees;
    }
    void CreateSoftware() {
        // ...
        std::vector<Employee*> employees = getEmployees();
        for (Employee* employee : employees) {
            employee->doWork();
        }
    }
}; // OutsourcingCompany is Concrete

/*
Company and Employee are independant of each various
types of each other. Neither is bound to any specific
type of the other. That is also this example serves to
prove.

New Company and Employee type classes can be added without
breaking any code and the Abstract class can be extended
without breaking any code.
*/

// Example 2:

class Transport {
    public:
        virtual void deliver() = 0;
}; // Interface
class Truck: public Transport {
    private:
    // ...fields
    public:
        void deliver() {
            // ... Deliver by land in a box.
        }
};
class Ship: public Transport {
    private:
    // ...fields
    public:
        void deliver() {
            // ... Deliver by sea in a container.
        }
};
class Logistics {
    private:
    // ...fields
    public:
        virtual Transport* createTransport() = 0; // You can provide a default if you wish to do so.
        void planDelivery() {
            Transport* t = createTransport();
            t->deliver();
        }
}; // Abstract class
class RoadLogistics: public Logistics {
    private:
    // ...fields, like object pool or cache
    std::vector<Truck*> fleet;
    public:
        Truck* createTransport() {
            if (fleet.empty())
                fleet.push_back(new Truck());
            Truck* t =  fleet.back();
            fleet.pop_back();
            return t;
        }
};
class SeaLogistics: public Logistics {
    private:
    // ...fields
    public:
        Ship* createTransport() {
            return new Ship();
        }
};