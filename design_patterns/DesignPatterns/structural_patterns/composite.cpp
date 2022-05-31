#include <iostream>
#include <vector>
#include <algorithm> // std::remove
#include <array>

class Graphic {
    public:
        Graphic();
        virtual size_t getArea() = 0;
        virtual void move(size_t x, size_t y) = 0;
        virtual void draw() = 0;
}; // Interface.

class Dot : public Graphic {
    private:
        size_t x;
        size_t y;
    public:
        Dot(size_t x, size_t y) : x(x), y(y) {}
        size_t getArea() {
            return 0; // Dot has no area.
        }
        void move(size_t x, size_t y) {
            this->x = x;
            this->y = y;
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
        size_t getArea() {
            return 3.14 * radius * radius;
        }
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
        size_t getArea() {
            size_t area = 0;
            for (auto graphic : graphics) {
                area += graphic->getArea();
            }
            return area;
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