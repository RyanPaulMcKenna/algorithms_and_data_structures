# Facade
**Facade** is a structural design pattern that provides a simplified interface to a library, a framework, or any other complex set of classes.

#### :worried: Problem

You must make your code work with a broad set of objects that belong to a complex 3rd party, that require initalizations, dependencies and methods exectuted in specific orders etc.

As a result, your business logic would become tightly coupled to the implementation of 3rd-party classes.

#### :smiley: Solution

A facade is a class that provides a simple interface to a complex subsystem which contains lots of moving parts. It may provide limited functionality. However it includes only those features that clients really care about.


### In a nutshell
nstead of making your code work with dozens of the framework classes directly, you create a facade class which encapsulates that functionality and hides it from the rest of the code. This structure also helps you to minimize the effort of upgrading to future versions of the framework or replacing it with another one. The only thing you’d need to change in your app would be the implementation of the facade’s methods



### C++ Example

```c++
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
```

#### Structure

![facade uml](/Chapter3/diagrams/facade.png)

##### C++ Example: Video Converter

```c++
// START OF DEPENDENCIES
class VideoFile {
    public:
        void run() {}
};
class AudioMixer {};
class CodeFactory {};
class BitrateReader {};
class OggCompressionCodec {};
class MPEG4CompressionCodec {};
// END OF DEPENDENCIES

class VideoConverter {
    private:
        // ...DEPENDENCIES
    public:
        VideoFile convertVideo(std::string filename, std::string format) {}
};
class Application {
    private:
        //...fields
    public:
        Application() {}
        void runVideo() {
            VideoConverter* vc = new VideoConverter();
            VideoFile video = cv->convertVideo("Space Oddessy", "MPEG4");
            video.run();
        }
};
```


#### Applicability

* Use the Facade pattern when you need to have a limited but straightforward interface to a complex subsystem.

* Use the Facade when you want to structure a subsystem into layers.

#### Pros & Cons

* :heavy_check_mark: You can isolate your code from the complexity of a subsystem.
* :x: A facade can become a **god object** coupled to all classes of an app.



