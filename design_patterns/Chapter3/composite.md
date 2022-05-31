# Composite
##### *Also known as: Object Tree*

**Composite** is a structural design pattern that lets you compose objects into tree structures and then work with these strauctures as if they were individual objects.

### :worried: Problem
Using the Composite only makes sense when the core model of your app can be respresented as a tree.

Imagine you have two types of objects: **Products** and **Boxes**. A Box can contains several Products and Product can contains several Boxes.


*An order may comprise various products, packaged in boxes, which are package in bigger boxes and so on. The Whole structure looks like an upside down tree.*

### :smiley: Solution
The Composite pattern suggests that you work with **Products** and **Boxes** through a common interface which declares a method for calculating the total price.

Products return prices and Boxes return the total prices of the products the its box.
A box could even add some extra cost to the final price, such as packaing cost.


*The Composite pattern lets you run a behaviour recursively over all components of an object tree.*

#### Structure

![composite pattern](/Chapter3/diagrams/composite.png)

1. **Component** interface describes common operations to all elements of the tree.
2. **Leaf** is basic element of a tree that doesn't have sub-elements.
3. **Composite** is an element that has sub-elements: leaves and other composites.
4. **Client** works with all elements through the **Component** interface.

#### C++ Example of Composite Pattern

```c++
#include <iostream>
#include <vector>
#include <algorithm> // std::remove
class Graphic {
    public:
        Graphic();
        virtual void move(size_t x, size_t y) = 0;
        virtual void draw() = 0;
}; // Interface.

class Dot : public Graphic {
    private:
        size_t x;
        size_t y;
    public:
        Dot(size_t x, size_t y) : x(x), y(y) {}
        void move(size_t x, size_t y) {
            this->x += x;
            this->y += y;
        }
        void draw() {
            std::cout << "Dot at (" << x << ", " << y << ")" << std::endl;
        }
};

class Circle : public Dot {
    private:
        size_t radius;
    public:
        Circle(size_t x, size_t y, size_t radius) : Dot(x, y), radius(radius) {}
        void draw() {
            std::cout << "Circle at with radius " << radius << std::endl;
        }
};

class CompoundGraphics : public Graphic {
    private:
        std::vector<Graphic*> graphics;
    public:
        void add(Graphic* graphic) {
            graphics.push_back(graphic);
        }
        void remove(Graphic* graphic) {
            graphics.erase(std::remove(graphics.begin(), graphics.end(), graphic), graphics.end());
        }
        void move(size_t x, size_t y) {
            for (auto graphic : graphics) {
                graphic->move(x, y);
            }
        }
        void draw() {
            for (auto graphic : graphics) {
                graphic->draw();
            }
        }
};


class ImageEditor {
    CompoundGraphics* all;
    public: 
        void groupSelected(std::array<Graphic*, 1000> components) {
            CompoundGraphics* group = new CompoundGraphics();
            for (auto component : components) {
                group->add(component);
                all->remove(component);
            }
            all->add(group);
            all->draw();
        }
};
```

*The geometric shapes editor example.*


#### Applicability 

* Use the Composite pattern when you have to implement a tree-like object structure.

#### Pros & Cons

* :heavy_check_mark: You can work with complex tree structures more conveniently: use polymorphism and recursion to your advantage.
* :heavy_check_mark: Open/Closed Principle. You can introduce new element types into the app without breaking the existing code, which now works with the object tree.

* :heavy_check_mark: It might be difficult to provide a common interface for classes whose functionality differs too much. In certain scenarios, you’d need to overgeneralize the component interface, making it harder to comprehend.

* :x: It might be difficult to provide a common interface for classes whose functionality differs too much. In certain scenarios, you’d need to overgeneralize the component interface, making it harder to comprehend.

