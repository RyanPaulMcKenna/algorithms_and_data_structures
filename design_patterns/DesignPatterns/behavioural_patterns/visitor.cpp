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