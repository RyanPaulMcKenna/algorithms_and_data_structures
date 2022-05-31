# ADAPATER
*Also known as: Wrapper*

##### **Adapter** is a structura; design pattern that allows objects with incompatible interfaces to collaborate.


###### :worried: Problem
*You can't use the analytics library "as is" because it expects the data in JSON format that's incompatible with your XML app.*


###### :smiley: Solution
*You can create an adapter.* This is a special object that converts the interface of one object so that another object can understand it.


#### Here's how it works:
1. The adapter gets in interface, compatible with one of the existing objects.
2. Using this interface, the existing object can safely call the adpater's method.
3. Upon reciving a call, the adapter passes the request to the second object, but in a format and order that the second object expects.

*Sometimes it's even possible to create a two-way adapter that can convert the call in both directions.*

#### **Structure**

###### **Object adapter**

![object adapter](/Chapter3/diagrams/object_adapter.png)

1. **Client** class contains existing business logic.
2. **Client Interface** describes a protocol that other classes must follow to be able to collaborate with the client code.
3.  **Service** is some useful class (*Usually 3rd-party or legacy*). The client can;t use this class directly because it has an incompatible interface.
4. **Adapter** is a class that's able to work with both the client and the service: it implements the **Client Interface**, while wrapping the service object. The **Adapter** translates calls from the **Client** into calls to the wrapped service object in the correct format.
5. **Client** code doesn't get couple to the conrete adapter class as long as it work with the adpater via the client interface.

Alternatively there is the ***Class adapter***

This approach uses multiple inheritance.

![class adapter](/Chapter3/diagrams/class_adapter.png)


The **Class Adapter** doesn't need to wrap any objects because it inherits behaviours from both the client and the servce. The adapation happsn within the overrid methods. The resulting adapter can be used in place of an existing client class.

#### C++ Adapter pattern: Square peg round hole

```C++
#include <math.h>

class SquarePeg {
    private:
        int width;
    public:
        SquarePeg(int w): width(w) {}
        int getWidth() {
            return width;
        }
};
class RoundPeg {
    private:
        int radius;
    public:
        RoundPeg(): radius(0) {}
        RoundPeg(int r): radius(r) {}
        int getRadius() {
            return radius;
        }
};
class RoundHole {
    private:
        int radius;
    public:
        RoundHole(int r): radius(r) {}
        int getRadius() {
            return radius;
        }
        bool fits(RoundPeg peg) {
            return (peg.getRadius() <= radius);
        }
};

class SquarePegAdapter: public RoundPeg {
    private:
        SquarePeg peg;
    public:
        SquarePegAdapter(SquarePeg peg): peg(peg) {}
        int getRadius() {
            return peg.getWidth()*sqrt(2)/ 2;
        }
};
```

*Adapting square pegs to round holes.*

The Adapter pretends to be a round peg, with a radius equal to the diagonal of the square.

#### Applicability

* Use the Adapter class when you want to use some class, but its interface isn’t compatible with the rest of your code.

* The Adapter pattern can act as a translator between legacy code.

* Use the pattern when you want to reuse several existing sub-classes that lack some common functionality that can't be added to the superclass.

*Shares similarity with the ***Decorator*** pattern*

#### Pros & Cons

* :heavy_check_mark: *Single Responsibility Principle*
* :heavy_check_mark: *Open/Closed Principle*
* :x: The overall complexity of the code increases because you need to introduce a set of new interfaces and classses. Sometimes it is simpler jus to change the service class so that it matches the rest of your code.


