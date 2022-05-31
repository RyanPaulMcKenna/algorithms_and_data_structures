# BRIDGE

##### **Bridge** is a structural design pattern that lets you split a large class or a set of closely related claases into tow separte hierarchies-abstraction and implementation-which can be developed independently of each other.


#### :worries: Problem
You need loads of combinations **Shape** objects like: **RedCircle**, **RedSquare**, **RedTriangle** **BlueCircle**, **BlueSquare**, **BlueTriangle**, **GreenCircle**, **GreenSquare**, **GreenTriangle** as you can see the number of combinations is exploding exponentially.

#### :smiley: Solution
The problem occurs because we're trying to extend the **Shape** class into two independent dimensions: by form and by color, That's a very common issues with class inheritance.


The Bridge pattern attempts to solve this problem by switching from inheritance to object composition.

```c++
class Color {
};
class Red: public Color {
};
class Blue: public Color {
};
class Shape {
    private:
        Color c; // composition.
    public:
        // ...methods.
};
class Circle: public Shape {
};
class Square: public Shape {
};

```
*You can prevent the explosion of a class hierarchy by transforming it into several related hierarchies.*

The reference to the color object will act as a ***bridge*** between **Shape** and **Color** classes. Now adding new colors won't require changing the shape hierarchy.


*** The Gang of Four Book** introduces the terms *Abstraction* and *Implementation* as part of the Bridge definition. In the context that the **GOF** intended these various examples make it clear ***Graphical User Interfaces*** to an ***Operating Systems***, ***Television Remotes*** to a ***Televisions*** etc.


#### Remote controls and Devices Bridge Example in C++

```c++
#include <string>
#include <iostream>

class Device {
    public:
        virtual bool isEnabled() = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual size_t getVolume() = 0;
        virtual void setVolume(size_t) = 0;
        virtual size_t getChannel() = 0;
        virtual void setChannel(size_t) = 0;
}; // Interface

class Radio : public Device {
    bool enabled;
    size_t volume;
    size_t channel;
    // ... hardware-specific inforemation.
    public:
        Radio() : enabled(false), volume(10), channel(1) {}
        bool isEnabled() { return enabled; }
        void enable() { enabled = true; }
        void disable() { enabled = false; }
        size_t getVolume() { return volume; }
        void setVolume(size_t volume) { volume = volume; }
        size_t getChannel() { return channel; }
        void setChannel(size_t channel) { channel = channel; }
};
class TV : public Device {
    bool enabled;
    size_t volume;
    size_t channel;
    // ... hardware-specific inforemation.
    public:
        TV() : enabled(false), volume(10), channel(1) {}
        bool isEnabled() { return enabled; }
        void enable() { enabled = true; }
        void disable() { enabled = false; }
        size_t getVolume() { return volume; }
        void setVolume(size_t volume) { volume = volume; }
        size_t getChannel() { return channel; }
        void setChannel(size_t channel) { channel = channel; }
};

class Remote { // Abstraction Object, by GOF terminology
    private:
        Device *device; // Implementation object, by GOF terminology
    public:
        Remote(Device *device) : device(device) {}
        void togglePower() {
            if (device->isEnabled()) {
                device->disable();
            } else {
                device->enable();
            }
        }
        void volumeUp() {
            device->setVolume(device->getVolume() + 1);
        }
        void volumeDown() {
            device->setVolume(device->getVolume() - 1);
        }
        void channelUp() {
            device->setChannel(device->getChannel() + 1);
        }
        void channelDown() {
            device->setChannel(device->getChannel() - 1);
        }
};

class AdvancedRemote: public Remote {
    public:
        AdvancedRemote(Device *device) : Remote(device) {}
        void VoiceCommandChangeChannel(std::string voiceCommand) {
            std::cout << "Yes sir, I will change the channel" << std::endl; 
            if (voiceCommand == "channel up") {
                channelUp();
            } else if (voiceCommand == "channel down") {
                channelDown();
            }
        }
};

class Client {
    public:
        void test() {
            Radio radio;
            TV tv;
            Remote radioRemote(&radio);
            Remote tvRemote(&tv);
            AdvancedRemote advancedRemote(&tv);
            radioRemote.togglePower();
            tvRemote.togglePower();
            advancedRemote.VoiceCommandChangeChannel("channel up");
        }
};

int main() {
    Client client;
    client.test();
    return 0;
}
```


#### Applicability 

* Use the Bridge pattern when you want to divide and organize
a monolithic class that has several variants of some functionality (for example, if the class can work with various database
servers).

* Use the pattern when you need to extend a class in several
orthogonal (independent) dimensions.

* Use the Bridge if you need to be able to switch implementations at runtime.

*Remeber a pattern is more than just a way to structure your classes. It may also communciate intent ans a problem being addressed.*

#### Pros & Cons

* :heavy_check_mark: You can create platform-independent classes and apps.

* :heavy_check_mark: The client work with high-level abstractions.

* :heavy_check_mark: *Open/Closed Principle* Introduce new abstractions and implmentations independently from each other.

* :heavy_check_mark: *Single Responsibility Principle* Focus on high-level logic in the abstraction and on platform details in the implementation.

* :x: You might make the code more complicated by applying the pattern to a highly cohesive class.

*You can use ***Abstract Factory*** along with ***Bridge***. This pairing is useful when some abstractions defined by Bridge can only work with specific **implmentations**. In this case, Abstract Factory can encapsulate these relations and hide the complexity from the client code.

