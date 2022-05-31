### Factory Method
*Virtual Constructor*
**Factory Method** is a creational design pattern that provides
an interface for creating objects in a superclass, but allows
subclasses to alter the type of objects that will be created.

***The Problem*** 
Imagine creating a logistics app. The first version can only handle transport via trucks, so all the code lives in the **Truck** class. After a while, your app becomes very popular. You receive dozens of requests from sea transport companies to add sea logistics to the app.

***The Solution***
The Factory Method pattern suggets that you replace direct object construction calls (using ***new***) with calls to a special *factory* method.  Objects returns by a factory method are oftern referred to as *products*.

```c++
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
```

The Limitation here that subclasses can only return different types of *products* if these *products* have a common base class or interface.

The client code that calls the factory method treats all the products as abstract ***Transport***

![Factory Method](/Chapter2/diagrams/factory_method.png)

Note, despite its name, the creator's primary responsibility is not to create products. Usually the creator already has some core business logic related to products. 
***Analogy***: a large software development company can have a training department for programmers.
However, the primary function of the comapyn as whole is still writing code, not producing programmers.

Note, the factory method, doesn't have to **create** new instances all the time. It can also return existing objects from a chage, an object pool, or another source.

#### Applicability
* Use the Factory Method when you don't know beforehand the exact types and dependencies of the objects your code should work with.

* Use the Factory Method when you want to provide users of
your library or framework with a way to extend its internal
components.

* Use the Factory Method when you want to save system
resources by reusing existing objects instead of rebuilding
them each time.

#### Pros & Cons
* :heavy_check_mark: You avoid tight coupling between the creator and the concrete
products.

* :heavy_check_mark: Single Responsibility Principle. You can move the product creation code into one place in the program, making the code easier to support.

* :heavy_check_mark: Open/Closed Principle. You can introduce new types of products
into the program without breaking existing client code.

* :x: The code may become more complicated since you need to
introduce a lot of new subclasses to implement the pattern.
The best case scenario is when you’re introducing the pattern
into an existing hierarchy of creator classes


