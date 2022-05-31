// These Subsystems a parts of a large complex system requiring
// specific initalizations and method calls in specific orders. 
#include <iostream>
class SubSystemOne {
    // very complex logic.
    public:
        SubSystemOne() {}
        SubSystemOne(int, int, int , int , int , int) {}
        int MethodOne(float f) { return (int) f;}
};
class SubSystemTwo {
    // very complex logic.
    public:
        SubSystemTwo() {}
        SubSystemTwo(float, float, float, float, float, float ) {}
        float MethodTwo(float f) { return f;}
};
class SubSystemThree: public SubSystemOne {
    // very complex logic.
    public:   
        SubSystemThree() {}
        SubSystemThree(double, double, double, double, double, double) {}
        double MethodThree(float f) { return (double) f;}
};
class SubSystemFour: public SubSystemTwo {
    // very complex logic.
    public:
        SubSystemFour() {}
        SubSystemFour(char, char, char, char, char, char) {}
        char MethodFour(double d) { return (char) d;}
};

// The Facade class encapsulates all of the subsystems and provides a simple
// interface to the client.
class AdditionalFacade {
    private:
        SubSystemOne *one;
        SubSystemTwo *two;
    public:
        AdditionalFacade() {
            int one_params[6] = {1,2,3,4,5,6};
            float two_params[6] = {1.1,2.2,3.3,4.4,5.5,6.6};
            one = new SubSystemOne(
                one_params[0], one_params[1], one_params[2],
                one_params[3], one_params[4], one_params[5]
            );
            two = new SubSystemTwo(
                two_params[0], two_params[1], two_params[2],
                two_params[3], two_params[4], two_params[5]
            );
        }
        float execute() {
            return one->MethodOne(two->MethodTwo(3.14));
        }
};
class Facade {
    private:
        AdditionalFacade *additional;
        SubSystemThree* three;
        SubSystemFour* four;
    public:
        Facade() {
            additional = new AdditionalFacade();
            double three_params[6] = {1.1,2.2,3.3,4.4,5.5,6.6};
            char four_params[6] = {'a','b','c','d','e','f'};

            three = new SubSystemThree(
                three_params[0], three_params[1], three_params[2],
                three_params[3], three_params[4], three_params[5]
            );
            four = new SubSystemFour(
                four_params[0], four_params[1], four_params[2],
                four_params[3], four_params[4], four_params[5]
            );
        }
        char execute() {
            return four->MethodFour(three->MethodThree(additional->execute()));
        }
    
};
class Client {
    public:
        Client() {}
        void run() {
            Facade *facade = new Facade();
            std::cout << "Result: " << facade->execute() << std::endl;
        }
};

int main() {
    Client *client = new Client();
    client->run(); // Prints out a heart.
    return 0;
}
