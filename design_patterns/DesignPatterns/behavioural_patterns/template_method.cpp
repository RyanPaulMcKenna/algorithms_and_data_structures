#include <iostream>
#include <utility>

// ABSTRACT CLASS
class GameAI {
    private:
    //...
    public:
        virtual void takeTurn() = 0;
        virtual void collectResources() = 0;
        virtual void buildStructures() = 0;
        virtual void buildUnits() = 0;
        virtual void attack() = 0;
        virtual void sendScouts(std::pair<int, int> pos) = 0;
        virtual void sendWarriors(std::pair<int, int> pos)  = 0;
};

// CONCRETE CLASSES
class OrcsAI: public GameAI { 
    private:
        void takeTurn() {
            std::cout << "Orcs take turn" << std::endl;
        }
        void collectResources() {
            std::cout << "Orcs collect resources" << std::endl;
        }
        void buildStructures() {
            std::cout << "Orcs build structures" << std::endl;
        }
        void buildUnits() {
            std::cout << "Orcs build units" << std::endl;
        }
        void attack() {
            std::cout << "Orcs attack" << std::endl;
        }
        void sendScouts(std::pair<int, int> pos) {
            std::cout << "Orcs send scouts to: " << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
        void sendWarriors(std::pair<int, int> pos) {
            std::cout << "Orcs send warriors to "  << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
};

class MonstersAI : public GameAI {
    private:
        void takeTurn() {
            std::cout << "Monsters take turn" << std::endl;
        }
        void collectResources() {
            std::cout << "Monsters collect resources" << std::endl;
        }
        void buildStructures() {
            std::cout << "Monsters cannot build structures" << std::endl;
        }
        void buildUnits() {
            std::cout << "Monsters cannot build units" << std::endl;
        }
        void attack() {
            std::cout << "Monsters attack" << std::endl;
        }
        void sendScouts(std::pair<int, int> pos) {
            std::cout << "Monsters send scouts to: " << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
        void sendWarriors(std::pair<int, int> pos) {
            std::cout << "Monsters send warriors to " << " (" <<  pos.first << "," << pos.second << ")" << std::endl;
        }
};

int main() {
    GameAI* orcs = new OrcsAI();
    GameAI* monsters = new MonstersAI();

    std::cout << "Orcs" << std::endl;
    orcs->takeTurn();
    orcs->collectResources();
    orcs->buildStructures();
    orcs->buildUnits();
    orcs->attack();
    orcs->sendScouts(std::make_pair(1, 2));
    orcs->sendWarriors(std::make_pair(3, 4));

    std::cout << "Monsters" << std::endl;
    monsters->takeTurn();
    monsters->collectResources();
    monsters->buildStructures();
    monsters->buildUnits();
    monsters->attack();
    monsters->sendScouts(std::make_pair(5, 6));
    monsters->sendWarriors(std::make_pair(7, 8));
    return 0;
}