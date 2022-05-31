# Design Principles

## Encapsulate what varies
Isolate the parts of the program that
vary in independent modules, protecting the
rest of the code from adverse effects.
### Encapsulation on a Method level
The code that is likely to change within a function
should be in its own separate function not mixed
with the rest of the code that is not likely to change.

### Encapsulation on a Class level
The code that is likely to change within a class
should be inits own separate class that works with
the existing class via *composition* for example.


## Program to an Interface, not an Implementation
You can tell the design is flexible enough if you can
easily extend it without breaking any existing code.

An implementation is circumstancial
Cat eats sausage
An Interface is general
Cat eats food of type sausage

Getting all food items to implement a food interface
makes the interaction between classes more extensible
now the cat could eat a variety of food items and the
Cat class will not need to change to accomodate this
it can eat any food with the same eat function.

In general, classes should not depend on each other directly but depend on certain behaviours in situations
where there are likely to many varieties of similar the same thing like companies and employees both come in vast variety of types.


## Favour Composition or Aggregation Over Inheritance
### Inheritance "is a" relationship drawbacks, car is a transport
* Subcalss Cant reduce interface of the superclass
* Overriding methods must be compatible with base ones
* parallel inheritance hierarchies can lead to bloated combinatorial explosion of *subclass*es.
### Composition "has a" relationship, car has an engine

### Aggregation "has a" relationship without lifecyle dependance, car has a driver


# SOLID Principles, guidelines not rules.
Originally introduced by Robert Martin in the book Agile Software Development, 
Principles, Patterns and Practices.

Mnemonic for five design principles to make software designs more understandable, flexible
and maintainable.


## Single Responsibility Principle
**A class should have just one reason to change.**
Ideally a class should be responsible for a single part of the functionaity provided by the software.
That single responisbility should be **entirley** *hidden* within the class.

Helps to reduce complexity.
*Break single class with many behaviours into many classes with single behavior*


## Open/Closed Principle
**Classes should be open for extension but closed for modification.**
The main idea of this principle is to keep existing code from
breaking when you implement new features.
### For example:
    Instead of changing the code of the
    class directly, you can create a *subclass* and override parts of
    the original class that you want to behave differently. You’ll
    achieve your goal but also won’t break any existing clients of
    the original class.

*Strategy Pattern*

## Liskov Substitution Principle
*When extending a class, remember that you should be able to pass objects of the *subclass* in place of objects
of the parent class without breaking the client code*

This means that the *subclass* should remain compatible with the behaviour of the superclass.
When overriding a method, extend the base behaviour rather than replacing it with some-
thing else entirely.

### Checklist
* Parameter types in a method of a *subclass* should *match* or be more abstract than parameter types in
the method of the superclass. 
Good: *subclass*.feed(Animal C), superClass.feed(Cat c)

* The return type in a method of a *subclass* should *match* or be a subtype of the return type in the
method  of the superclass. *subclass*.buyCat(): BengalCat, superClass.buyCat(): Cat

* A method in a *subclass* shouldn't throw types of exceptions which the base method isn't expected
to throw. Types of Exceptions should *match* or be subtypes of the ones that the base method is
already able to throw.

* A subclass shouldn’t strengthen pre-conditions. Example: Base method has parameter of type int. If a subclass overrides this method and requires that the value of argument passed to the method should be positive this strengthens the pre-conditions, Client code that works with the base class now breaks if it starts working with an object of this subclass when a negative number is passed which was fine with the base class. 


* A subclass shouldn't weaken post-conditions. Base class method closes database connections when done using them. A subclass does not close the database connections when it is done. Client code that worked with the base
class could be polluted with ghost databse connections.

* Invariants of a superclass must be preserved. *Invariants* are conditions in which an object makes sense.
For example, invariants of a cat are having four legs, a tail, ability to meow, etc. Can be defined in the
form of an interface, a set of assertions or implied by certain unit tests or expectations of the client code.

* A subclass shouldn;t change values of private fields of the superclass.

## Interface Segregation Principle
*Clients shoudldn't be forced to depend on methods they do not use.*

Try to make your interfaces narrow enough that client classes
don’t have to implement behaviors they don’t need.


Class inheritance lets a class have just one superclass, but it
doesn’t limit the number of interfaces that the class can implement at the same time. Hence, there’s no need to cram tons
of unrelated methods to a single interface. Break it down into
several more refined interfaces—you can implement them all
in a single class if needed. However, some classes may be fine
with implementing just one of them.

```c++
class IParrotVendor {
    // no fields..
    public:
    virtual void sellParrots() = 0; 
}; // Interface

class IRabbitVendor {
    // no fields..
    public:
    virtual void sellRabbit() = 0; 
}; // Interface
class ParrotBreeder: public IParrotVendor {
    void sellParrots() {
        //...sellParrots
    }
};
class RabbitBreeder: public IRabbitVendor {
    void sellRabbit() {
        // ..sellRabbits
    }
};
class PetShop: public IRabbitVendor, public IParrotVendor {
    void sellParrots() {
        //...sellParrots
    }
    void sellRabbit() {
        // ..sellRabbits
    }
}
```

## Dependency Inversion Principle

*High-level classes shouldn't depend on low-level classes. Both should depend on abstrations.
Abstrations shouldn't depend on details. Detail should depend on abstrations*

* Low-level classes implement basic operations
* High-level classes contain complex business logic that directs low-level classes to do something.

To start you need to describe **interfaces for low-level operations** that high-level classes can rely on
preferably in business terms. Example business logic should call a method openReport(file) rather than 
a series of low level methods openFile(x), readBytes(n), closeFile(x), so that a high-level class depends on
a high-level interface and not a low one.

*The Dependency Inversion Principle often goes along with the open/closed principle*

### *BEFORE: a high-level class depends on a low-level class.*
```c++
// Low level
class MySQLDatabase {
    private:
    // ...
    public:
        void insert();
        void update();
        void delete();
};
//  High level
class BudgetReport {
    private:
        MySQLDatabase* database;
    public:
        void open();
        void save();
};
```

### *AFTER: low-level classes depend on a high-level abstration.*
```c++
//  High level Interface
class IDatabase {
    public:
        virtual void insert() = 0;
        virtual void update() = 0;
        virtual void delete() = 0;
};
// High level class
class BudgetReport {
    private:
        IDatabase* database;
    public:
        void open();
        void save();
};

// Low level implementation class
class MySQLDatabase: public IDatabase {
    private:
    // ...
    public:
        void insert() {
            // ...
        }
        void update() {
            // ...
        }
        void delete() {
            // ...
        }
};
```

*As a result, the direction of the original dependency has been invertedL low-level classes
are now dependent on high-level abstrations.*