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