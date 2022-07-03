# MEDIATOR
***Also known as: intermediary, Controller***

**Mediator** is a behavioural design pattern that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forcs them to collaborate only via a mediator object.

# The Problem
*Elements have lots of relations with other elements. Hence, changes to some elements may affect the others.*

# The Solution
Cesase all direct communication between components and instead all elements communicate indirectly, via the mediator object. Coupling them thm all to one mediator object instead of dozens of their colleqgue elements.

The container class that knows about all the elements will usually become the mediator object.
You can make this dependency looser by extracting a common interface for all types of objects.
All elements will have a notify method inherited from the interface.

***The fewer dependencies a class has, the easier it becomes to modify, extend or reuse that class.***

## Real-World Analogy
Like various aircraft communicating through the control tower to decide who lands first.

### Structure

```c++
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
```

### Applicability
Use the Mediator pattern when it’s hard to change some of the
classes because they are tightly coupled to a bunch of other
classes.

### Pros and Cons

* :heavy_check_mark: *Single Responsibility Principle*
* :heavy_check_mark: *Open/Closed Principle*
* :heavy_check_mark: Reduce coupling
* :heavy_check_mark: Promotes code reuse
* :x: over time a mediator can evolve into a **God Object**

