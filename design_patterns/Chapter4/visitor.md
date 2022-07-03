# VISITOR
**Visitor** is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.

# The Problem
You have a bunch of classes that are similar and they need a new behavior that doesn't really have anything to do with the object's semantic representation. 

For example:
Geographic information structures as a colossal graph may represent a complex entity such as a city, industries, sightseeing areas, etc. Now you need the ability to serialize all of these entities into XML and maybe other formats as well.
These behaviors don't have anything to with geographic data so adding it to the those classes is clearly ugly, wrong and violates
*Single Responsibility Principle* and possibly other things too.

# The Solution
Visitor lets you add “external” operations to a whole class hierarchy without changing the existing code of these classes.

The Visitor method is built upon the double dispatch principle.

# Double Dispatch
The method uses a technique called **Double Dispatch**,
which helps to execute the proper method on an objects without cumberson conditionals. 

The idea is the visitor's visit method has overloads for different classes of objects and those classes have an accept method that "accepts" a parameter of type **visitor**. The visitor's visit method is called with the parameter of the "this" pointer of class it is visiting. The correct overload will be called from the visitor, avoiding the need for any conditionals whilst providing a mechanism of directing different calls for different object types.

# Structure

![visitor pattern](/chapter4/diagrams/visitor.png)


# C++ Implementation: Shapes requriring XML Export

```c++
#include <iostream>
#include <utility>

// Strangely I had to declare the subclass names before the base class to make this work.

// The Double Dispatching technique is used.

class Dot;
class Circle;
class Rectangle;
class CompoundShape;

// INTERFACES
class Visitor {
    public:
        virtual void visit(Dot* d) = 0;
        virtual void visit(Circle* c) = 0;
        virtual void visit(Rectangle* r) = 0;
        virtual void visit(CompoundShape* cg) = 0;
};
class Shape {
    public:
        virtual void move(std::pair<int,int> pos) = 0;
        virtual void draw() = 0;
        virtual void accept(Visitor* v) = 0;
};
// CONCRETE CLASSES
class Dot: public Shape {
    public:
        void move(std::pair<int,int> pos) override {
            std::cout << "Dot moved to " << pos.first << "," << pos.second << std::endl;
        }
        void draw() override {
            std::cout << "Dot drawn" << std::endl;
        }
        void accept(Visitor* v) {
            v->visit(this);
        }
};
class Circle : public Shape {
    public:
        void move(std::pair<int,int> pos) override {
            std::cout << "Circle moved to " << pos.first << "," << pos.second << std::endl;
        }
        void draw() override {
            std::cout << "Circle drawn" << std::endl;
        }
        void accept(Visitor* v) {
            v->visit(this);
        }
};
class Rectangle : public Shape {
    public:
        void move(std::pair<int,int> pos) override {
            std::cout << "Rectangle moved to " << pos.first << "," << pos.second << std::endl;
        }
        void draw() override {
            std::cout << "Rectangle drawn" << std::endl;
        }
        void accept(Visitor* v) {
            v->visit(this);
        }
};
class CompoundShape : public Shape {
    public:
        void move(std::pair<int,int> pos) override {
            std::cout << "CompoundShape moved to " << pos.first << "," << pos.second << std::endl;
        }
        void draw() override {
            std::cout << "CompoundShape drawn" << std::endl;
        }
        void accept(Visitor* v) {
            v->visit(this);
        }
};


class XMLExportVisitor: public Visitor {
    public:
        void visit(Dot* d) {
            std::cout << "Dot exported to XML" << std::endl;
            // Call getter and setters of Dot class to serialize it and then convert to XML within this function.
        }
        void visit(Circle* c) {
            std::cout << "Circle exported to XML" << std::endl;
            // Call getter and setters of Circle class to serialize it and then convert to XML within this function.
        }
        void visit(Rectangle* r) {
            std::cout << "Rectangle exported to XML" << std::endl;
            // Call getter and setters of Rectanle class to serialize it and then convert to XML within this function.
        }
        void visit(CompoundShape* cg) {
            std::cout << "CompoundShape exported to XML" << std::endl;
            // Call getter and setters of CompoundShape class to serialize it and then convert to XML within this function.
        }
};

int main() {
    Dot* dot = new Dot();
    Circle* circle = new Circle();
    Rectangle* rectangle = new Rectangle();
    Visitor* v = new XMLExportVisitor();
    v->visit(dot);
    v->visit(circle);
    v->visit(rectangle);

}
```

# Applicability

Use the **Visitor** pattern when you need to perform an operation on all elements of a complex object structure (for example, an object tree).

Use the **Visitor** to clean up the business logic of auxiliary behaviors.

# Pros and Cons

* :heavy_check_mark: *Open/Closed Principle*. You can introduce a new behavior that can work with objects of different classes without changing these classes.
* :heavy_check_mark: *Single Responsibility Principle*. You can move multiple versions of the same behavior into the same class.
* :heavy_check_mark: A **Visitor** object can accumulate some useful information whilst working with various objects. This might be handy if you want to traverse some complex object structure like a tree or graph.
* :x: You need to update all visitors each time a call gets added to or removed from the element hierarchy.
* :x: Visitors might lack the necessary access to the private fields and methods of the elements that they're supposed to work with.
