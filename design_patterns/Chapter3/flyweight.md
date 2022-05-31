# FLYWEIGHT
*Also known as Cache*

**Flyweight** is a structural design pattern that lets you fit more objects into the available amount of RAM by sharing common parts of state between multiple objects instead of keeping all of the data in each object.


*The constant data of an object is called the intrinsic state.*

*The data that is subject to change is called the extrinsic state.*

A Flyweight is an object that only stores the intrinsic state.
The extrinsic state is moved to a class that aggregates the Flyweight object.

Now, a thousand small contextual objects can reuse a single heavy flyweight object instead of storing a thousand copies of its data.

## Flyweight objects should be immutable
All the intrinsic state should be set in the constructor. It shouldn't expose any setters or or public fields.

```c++
class Particle {
    private: // Intrinsic state.
       std::string color;
       std::ofstream sprite;
    public:
        Particle(std::string color, std::ofstream sprite): color{color}, sprite{sprite} {}
        void move(std::pair<int,int> coords, std::pair<double,int> _vector, double speed) {}
        void draw(std::pair<int,int> coords, char canvas[][]) {}
};
class MovingParticle {
    private: // Extrinsic state.
        Particle* particle;
        std::pair<int,int> coords;
        std::pair<int,int> _vector;
        double speed;
    public:
        MovingParticle(Particle* p): particle{p} {}
        void move() {}
        void draw() {}
};
class Game {
    private:
        enum spriteType = { bullet, misssile, fireball, harpoon };
        std::vector<MovingParticles*> mps;
        std::vector<Particles*> particles;
    public:
        void addParticle(std::pair<int,int> coords, std::pair<double,int> _vector, double speed, std::string color, std::ofstream sprite) {}
        void addMovingBullets(size_t n) {
            
            Particle* p = particles[spriteType.bullet];
            for (size_t i = 0; i < n; ++i) {
                MovingParticle mp = new MovingParticle(p); 
                // Same bullet particle every time, the intrinsic data is not duplicated.
                mps.push_back(mp);
            }

        }
        void draw(char canvas[][]) {}
};

```

The Flyweight pattern is merely an optimization. Before applying make sure your program does has the RAM consumption problem related to having a massive number of similar objects in memory at the same time.

## Flyweight factory

For more convenient access to various flyweight, you can create a **Flyweight Factory**.

The Flyweight Factory manages a pool of existing flyweights. With the factory, clients don't create flyweights directly. Instead, they call the factory,passing it bits of the intrinsic state of the desire flyweight. The factory looks over previously created flyweights and either returns an existing one that matches search criteria or creates a new on if nothing is found.

```C++
class TreeType { // This is the flyweight. with the intrinsic data.
    private:
        std::string name;
        std::string color;
        std::string texture;
    public:
        TreeType(std::string name, std::string color, std::string texture): name{name}, color{color}, texture{texture} {}
        void draw(char canvas[][], size_t x, size_t y) {}
};
class Tree { // Thie is the extrinsic data.
    private:
        size_t x;
        size_t y;
        TreeType* type;
    public:
        Tree(size_t x, size_t y, TreeType* type): x{x}, y{y}, type{type} {}
        void draw(char canvas[][]) {
            type.draw(canvas, x, y);
        }

};

class TreeFactory { // Flyweight factory.
    private:
        std::vector<TreeType*> treeTypes;
    public:
        TreeFactory() {}
        TreeType* getTreeType(std::string name, std::string color, std::string texture) {
            for (TreeType* tt : treeTypes) {
                if (tt.name == name && tt.color == color && tt.texture == texture) {
                    return tt; // return if it exists.
                }
            }
            // else, make a new one. lazy creation.
            TreeType* tt = new TreeType(name, color, texture);
            treeTypes.push_back(tt);
            return tt;
        }
};


class Forest { 
    // Forest uses the factory to create trees whilst reusing the flyweight tree types.
    // so that the intrinsic data is not duplicated.
    private:
        TreeFactory* treeFactory;
    public:
        std::vector<Tree*> trees;
        Forest(TreeFactory* tf): treeFactory{tf} {}
        Tree* plantTree(size_t x, size_t y, std::string name, std::string color) {
            TreeType* type = treeFactory->getTreeType(name, color, "pine");
            Tree* t = new Tree(x, y, type);
            trees.push_back(t);
            return t;
        }
        void draw(char canvas[][]) {
            for (Tree* t : trees) {
                t->draw(canvas);
            }
        }
};
```


In this example, the **Flyweight** pattern helps to reduce memory usage when rendering millions of tree objects on a canvas.

#### Pros & Cons

* :heavy_check_mark: You can save lots of RAM, assuming your program has tons of similar objects.
* :heavy_check_mark: You might be trading RAM over CPU cycles when some of the context data needs to be recalculated each time somebody calls a flyweight method.
* :x: The code becomes much more complicated. New team members will always be wondering why the state of an entity was separated in such a way.


#### Tips
*You can implement shared leafS nodes of the ***Composite*** tree as ***Flyweights*** to save some RAM*

*Flyweights are immutable.*

