#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

#define MAX_ROWS 100
#define MAX_COLS 100

class Particle {
    private: // Intrinsic state.
       std::string color;
       std::ifstream sprite;
    public:
        Particle(std::string color, std::string sprite): color{color} {}
        void move(std::pair<int,int> coords, std::pair<double,int> _vector, double speed) {}
        void draw(std::pair<int,int> coords, char canvas[MAX_ROWS][MAX_COLS]) {}
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
        enum spriteType { bullet, misssile, fireball, harpoon };
        std::vector<MovingParticle*> mps;
        std::vector<Particle*> particles;
    public:
        void addParticle(std::pair<int,int> coords, std::pair<double,int> _vector, double speed, std::string color, std::string sprite) {}
        void addMovingBullets(size_t n) {
            Particle* p = particles[spriteType::bullet];
            for (size_t i = 0; i < n; ++i) {
                MovingParticle* mp = new MovingParticle(p); 
                // Same bullet particle every time, the intrinsic data is not duplicated.
                mps.push_back(mp);
            }

        }
        void draw(char canvas[MAX_ROWS][MAX_COLS]) {}
};

class Unit {
    public:
        std::pair<int,int> coords;
        void fireAt(Unit *target, Game* game) {
            std::pair<int,int> targetCoords = target->coords;
            std::pair<int,int> vector = {targetCoords.first - coords.first, targetCoords.second - coords.second};
            double distance = sqrt(vector.first*vector.first + vector.second*vector.second);
            // further geometry to determine angle... 
            double angle;
            double weaponPower = 75.5;
            double speed = 100.5;
            std::pair<double,int> _vector = {angle,weaponPower};
            std::string color = "silver";
            std::string sprite = "bullet.png";
            game->addParticle(coords, _vector, speed, color, sprite);
        }
};


// Example 2: Flyweight factory

class TreeType { // This is the flyweight. with the intrinsic data.
    private:
        std::string name;
        std::string color;
        std::string texture;
    public:
        TreeType(std::string name, std::string color, std::string texture): name{name}, color{color}, texture{texture} {}
        void draw(char canvas[MAX_ROWS][MAX_COLS], size_t x, size_t y) {}
        std::string getName() { return name; }
        std::string getColor() { return color; }
        std::string getTexture() { return texture; }
};
class Tree { // Thie is the extrinsic data.
    private:
        size_t x;
        size_t y;
        TreeType* type;
    public:
        Tree(size_t x, size_t y, TreeType* type): x{x}, y{y}, type{type} {}
        void draw(char canvas[MAX_ROWS][MAX_COLS]) {
            type->draw(canvas, x, y);
        }

};

class TreeFactory { // Flyweight factory.
    private:
        std::vector<TreeType*> treeTypes;
    public:
        TreeFactory() {}
        TreeType* getTreeType(std::string name, std::string color, std::string texture) {
            for (TreeType* tt : treeTypes) {
                if (tt->getName() == name && tt->getColor() == color && tt->getTexture() == texture) {
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
        void draw(char canvas[MAX_ROWS][MAX_COLS]) {
            for (Tree* t : trees) {
                t->draw(canvas);
            }
        }
};