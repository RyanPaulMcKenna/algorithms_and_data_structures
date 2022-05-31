### Abstract Factory

**Abstract Factory** is a creational design pattern that lets you produce families of related objects without specifiying their concrete classes.

* A family **Chair** + **Sofa** + **CoffeeTable**
* Variants of this family. *Chair, sofa, CofeeTable* are available in variants: *Modern, Victorian, ArtDec*


The first theing the **Abstract Factory** pattern suggests is to explicitly declare interfaces of each distinct produce of the product family (e.g. Chair, Sofa or CoffeeTable). Then make all variants follow those interfaces.

```c++
class Chair {
    public:
        virtual bool hasLegs() = 0;
        virtual void sitOn() = 0;
}; // Interface
class VictorianChair: public Chair {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
}; /// Concrete class
class ModernChair: public Chair {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
};
class Sofa {
    public:
        virtual bool hasLegs() = 0;
        virtual void sitOn() = 0;
}; // Interface
class VictorianSofa: public Sofa {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
}; /// Concrete class
class ModernSofa: public Sofa {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
};
class CofeeeTable {
    public:
        virtual bool hasLegs() = 0;
        virtual void sitOn() = 0;
}; // Interface
class VictorianCoffeeTable: public CoffeeTable {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        boid sitOn() {}
}; /// Concrete class
class ModernCoffeeTable: public CofeeTable {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        boid sitOn() {}
};
```
*All variants of the same object must be moved to a single class hierarchy.*

The next move is to declare the *Abstract Factory - an interface with a list of creation methods of all proucts that are part of the product family; **createChair**, **createSofa**, **createCoffeeTable**.

```c++
class FurnitureFactory {
    public:
        virtual Chair* createChair() = 0;
        virtual CoffeeTable* createCoffeeTable() = 0;
        virtual Sofa* createSofa() = 0;
}; // Interface
class VictorianFurnitureFactory: public FurnitureFactory {
    private:
        // ..fields
    public:
        Chair* createChair() {
            Chair* c = new VictorianChair();
            return c;
        }
        CoffeeTable* createCoffeeTable() {
            CoffeeTable* ct = new VictorianCofeeTable();
            return ct
        }
        Sofa* createSofa() {
            Sofa* s = new VictorianSofa();
            return s;
        }
};
class ModernFurnitureFactory: public FurnitureFactory {
    private:
        // ..fields
    public:
        Chair* createChair() {
            Chair* c = new ModernChair();
            return c;
        }
        CoffeeTable* createCoffeeTable() {
            CoffeeTable* ct = new ModernCofeeTable();
            return ct
        }
        Sofa* createSofa() {
            Sofa* s = new ModernSofa();
            return s;
        }
}; 
```
*Each concrete class corresponds to a specific product variant.*

```c++
class Client {
    private:
        FurnitureFactory* factory;
    public:
        Client(FurnitureFactory* f): factory{f} {} // Aggregation.
        void orderStock() {
            factory->createChair();
            factory->createSofa();
            factory->createCoffeeTable();   
        }
};

int main() 
{
    // Example 1: class can work with any type of FurnitureFactory
    FurnitureFactory* ff = new VictorianFurnitureFactory();
    Client c(ff);
    c->orderStock();

    // Example 2: Different FurnitureFactory objects can work as one type in an array.
    size_t CountSuppliers = 2;
    FurnitureFactory* supplierA = new VictorianFurnitureFactory();
    /*
    .
    .
    . Various furniture factories 
    */
    FurnitureFactory* supplierB = new ModernFurnitureFactory(); 
    FurnitureFactory* suppliers[countSuppliers] = {supplierA, supplierB};
    for (FurnitureFactory* ff : suppliers)
    {
        ff->createChair();
        ff->createSofa();
        ff->createCoffeeTable();
    }
}
```

*The client shouldn't care about the conrete class of the factory it works with*

Notes:
* All concrete products must be implemetned in all given variants
* Each Factory subclass creates only one type of variant
* Concrete factories must return abstract products

*The **Client** can work with any concrete factory/product variant, as long as it communicates with their objects via abstract interfaces.*

#### Applicability

* use the ***Abstract Factory*** paattern when your code needs to work with variou sfamilies of related prodcuts, but you don't want it to depend on the conrete classes of those products - they might be unknown beforehand or you simply want to allow for future extensibility.

* In a well-designed program each class is responsible only for
one thing. When a class deals with multiple product types,
it may be worth extracting its factory methods into a standalone factory class or a full-blown Abstract Factory implementation

#### Pros & Cons

* :heavy_check_mark: You can be sure all the products your getting from a factory are compatible with each other.

* :heavy_check_mark: You avoid tight coupling between conrete products and client code.

* :heavy_check_mark: *Single Responsibility Principle.* You can extract product creation code into one place. 

* :heavy_check_mark: *Open/Close Principle.* You can introduce new variants of products without breaking existing client code.

* :x: The code may become more complicated than it should be since a lot of new interfaces and classes are introduced along with the pattern.


#### Extra Information

* **Abstract Factory** classes are often based on a set of **Factory-Methods**, but you can also use **Prototype** to compose the method on these classes.

* **Abstract Factory**, **Builders** and **Prototypes** can all be implemented as **Singletons**.


