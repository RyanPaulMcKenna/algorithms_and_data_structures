#include <iostream>

enum Component { A, B, C, D};

// MEDIATOR INTERFACE
class Mediator {
    public:
        virtual void notify(Component sender) = 0;
};
class ConcreteMediator;
// ELEMENTS THAT NEEDS TO COLLABORATE
class ComponentA {
    friend class ConcreteMediator; // This should be dependant on the interface not the concrete class not sure how to work around it.
    private:
        Mediator* m;
    public:
        void operationA() {
            // ...
            std::cout << "ComponentA calls operationA" << std::endl;
            m->notify(Component::A);
        }
};
class ComponentB {
    friend class ConcreteMediator;
    private:
        Mediator* m;
    public:
        void operationB() {
            // ...
            std::cout << "ComponentB calls operationB" << std::endl;
            m->notify(Component::B);
        }
};
class ComponentC {
    friend class ConcreteMediator;
    private:
        Mediator* m;
    public:
        void operationC() {
            // ...
            std::cout << "ComponentC calls operationC" << std::endl;
            m->notify(Component::C);
        }
};
class ComponentD {
    friend class ConcreteMediator;
    private:
        Mediator* m;
    public:
        void operationD() {
            // ...
            std::cout << "ComponentD calls operationD" << std::endl;
            m->notify(Component::D);
        }
};
class ConcreteMediator: public Mediator {
    private:
        // Can be aggregation or composition, this example uses aggrgation.
        ComponentA* _a;
        ComponentB* _b;
        ComponentC* _c;
        ComponentD* _d;
    public:
        ConcreteMediator(ComponentA* a, ComponentB* b, ComponentC* c, ComponentD* d) {
            a->m = this;
            b->m = this;
            c->m = this;
            d->m = this;
            _a = a;
            _b = b;
            _c = c;
            _d = d;
        }
        void notify(Component sender)
        {
            switch(sender)
            {
                case Component::A: reactOnA(); break;
                case Component::B: reactOnB(); break;
                case Component::C: reactOnC(); break;
                case Component::D: reactOnD(); break;
                default: /*ERROR CONDITION*/ break;
            }
        }
        void reactOnA() {
            // ...
            std::cout << "ConcreteMediator reacts on A" << std::endl;
        }
        void reactOnB() {
            // ...
            std::cout << "ConcreteMediator reacts on B" << std::endl;
        }
        void reactOnC() {
            // ...
            std::cout << "ConcreteMediator reacts on C" << std::endl;
        }
        void reactOnD() {
            // ...
            std::cout << "ConcreteMediator reacts on D" << std::endl;
        }
};
//  USAGE:
int main() {
    ComponentA* a = new ComponentA();
    ComponentB* b = new ComponentB();
    ComponentC* c = new ComponentC();
    ComponentD* d = new ComponentD();
    Mediator* concMedi = new ConcreteMediator(a,b,c,d);

    a->operationA();
    b->operationB();
    c->operationC();
    d->operationD();

    return 0;
}