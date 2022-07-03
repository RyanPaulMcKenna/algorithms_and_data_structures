# MEMENTO
*Also known as snapshot*
**Memento** is a behavioral design pattern that lets you save and restore the previous state of an object without revealing the details of its implementation.

# The Problem
Text editor app needs the ability to undo any given action the user may have taken. Basic approach is to record the state of all objects before doing the action so your can restore the previous state if needed. Requiring complete public access to the objects is unsafe but without it we cannot create snapshots.

# The Solution
The Memento pattern delegates creating the state snapshots to the actual owner of that state, the *originator* object. The pattern suggests storing the copy of the object's state in a special object called *memento*. The contents of the memento are only accessible to the class that created it. Other objects communicate with it via a limited interface which may allow the fetching of metadata (creation time, name of the performed operation,etc.) but no the data.


![memento](/chapter4/diagrams/memento.png)

***The originator has full access to the memento, whereas the caretaker can only access the metadata.***

# Structure In c++
In reality many optimizations would be done that are not done here as
the objects are copied many times which can be avoided.

```c++

class Memento {
    private:
        // ..state
        Memento(/*..state*/);
        /*state*/ getState();
    public:
        // .. immutable.
};
class Originator {
    private:
        // ...state
    public:
        Memento save();
        void restore(m: Memento);
};
class Caretaker {
    private:
        Originator* originator;
        std::vector<Memento> history; // treat the vector like a stack.
    public:
        void doSomething()
        {
            Memento m = originator.save();
            history.push_back(m);
            // Originator.change()
        }
        void undo() {
            Memento m = history.pop_back();
            originator.restore(m);
        }
};

```


# C++ implementation

```c++

class Memento {

};
class ConcreteMemento : public Memento {
    private:
        //...state
    public:
        ConcreteMemento(/*...state*/);
        /**/ getState();
};
class Originator {
    private:
        //...state
    public:
        Memento* save();
        void restore(Memento* m);
};
class Client {
    private:
        Originator* originator;
        std::vector<Memento*> history;
    public:
        void undo();
}
```

# C++ Implementation Fully encapsulated version
```c++
#include <iostream>
#include <string>
#include<vector>

// INTERFACES
class Memento {
    public:
        virtual void restore() = 0;
};
class Originator {
    public:
        virtual Memento* save() = 0;
};
// CONRETE CLASSES
class Caretaker {
    private:
        std::vector<Memento*> history;
    public:
        void add(Memento* memento) {
// The original creates its own memento passes it to the caretaker
// and then changes its own state. The caretaker is completely decoupled.
            history.push_back(memento);
        }
        void undo() {
            if (history.size() > 0) {
                std::cout << "Restoring previous state" << std::endl;
                history.back()->restore();
                history.pop_back();
                return;
            }
            std::cout << "No more history to undo" << std::endl;
        }
};

class ConcreteOriginator : public Originator {
    private:
        std::string state;
    public:
        ConcreteOriginator(std::string state) {
            this->state = state;
        }
        Memento* save() override;
        void setState(std::string state) {
            this->state = state;
        }
        void getState() {
            std::cout << "Current state: " << state << std::endl;
        }
};
class ConcreteMemento : public Memento {
    private:
        ConcreteOriginator* originator;
        std::string state;
    public:
        ConcreteMemento(ConcreteOriginator* originator,std::string state) {
            this->originator = originator;
            this->state = state;
        }
        void restore() override {
            originator->setState(state);
        }
};

Memento* ConcreteOriginator::save() {
    return new ConcreteMemento(this,state);
}


int main() {
    Caretaker caretaker;
    ConcreteOriginator originator("Hello beautiful world");
    originator.getState();
    // USAGE
    Memento* memento = originator.save(); // save previous state
    caretaker.add(memento); // caretaker stores the memento.
    originator.setState("Goodebye cruel world"); // state changes
    originator.getState(); // display new state
    caretaker.undo(); // undo state changes
    originator.getState(); // display previous state
}
```

## Applicability
Use the Memento patternwhen you want to produce snapshots of the object's state to be able to restore a previous state of the object.

The Memento pattern is indispensable when dealing with transactions.

Use the pattern when direct access to the object's fields/getters/setters violates its encapsulation.

Original objects state is safe and secure becase only the object itself is presonsible for creating a snapshot or its state.

## Pros and Cons

* :heavy_check_mark: You can produce snapshots of the object's state without violating its encapsulation.

* :heavy_check_mark: You can simplify the orginator's code by letting the caretaker maintain the history.

* :x: The app might consume lots of RAM if clients creates too many mementos.

* :x: Caretakers should track the orginators lifecycle to be able to destroy obsolete mementos.

* :x: Dynamic languages like Python and JavaScript can't guarantee that the state within the memento stays untouched.

