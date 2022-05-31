### Prototype
*Also known as clone*

**Prototype** is a creational design pattern that lets you copy existing objects without making your code dependent on their classes.

*Cloning in the sense of miotic cell division not industrial prototyping, since these objects copy themselves.*

*Copying an object "from the outside" ***isn't*** always possible*

*Pre-build prototypes can be an alternative to subclassing.*

An object that supports cloning is called a *prototype*. When your objects have dozens of fields and hundreds of possible configurations, cloning them might serve as an alternative to subclassing.

```c++
class Prototype {
    private:
        string prototype_name;
    public:
        Prototype() {}
        Prototype(string prototype_name)
            : prototype_name(prototype_name) {

            }
        virtual Prototype* Clone() = 0;
}; // Interface

class ConcretePrototype: public Prototype {
    private:
        // ...fields
        int field1;
    public:
        ConcretePrototype(string prototype_name, int field1): Prototype(prototype_name), field1{field1} { }
        Prototype* Clone() const override {
            return new ConcretePrototype(*this);
        }
}; 
class SubclassPrototype: public ConcretePrototype {
    private:
        // ...fields
        float field2;
    public:
        SubclassPrototype(string prototype_name, int field1, float field2): ConcretePrototype(prototype_name, field1), field2{field2} { }
        Prototype* Clone() const override {
            return new SubclassPrototype(*this);
        }
}; 
class Client {
    public: 
        void test() {
            Prototype* p1 = new ConcretePrototype("p1", 1);
            Prototype* p2 = p1->Clone();
            Prototype* p3 = new SubclassPrototype("p3", 1, 2.0);
            Prototype* p4 = p3->Clone();
        }
};
```

#### Prototype registry implementation

![Prototype registry implementation](/Chapter2/diagrams/Prototype.png)


The **Prototype Registry** provides an easy way to access frequently used prototypes.
It stores a set of pre-built objects that are ready to be copied.

**Use the Prototype pattern when your code shouldn’t depend on the concrete classes of objects that you need to copy.**

This happens a lot when your code works with objects passed
to you from 3rd-party code via some interface. The concrete
classes of these objects are unknown, and you couldn’t depend
on them even if you wanted to.
The Prototype pattern provides the client code with a general interface for working with all objects that support cloning.
This interface makes the client code independent from the
concrete classes of objects that it clones.

#### Pros & Cons

* :heavy_check_mark: You can clone objects without coupling to their concrete
classes.
* :heavy_check_mark: You can get rid of repeated initialization code in favor of
cloning pre-built prototypes.
* :heavy_check_mark: You can produce complex objects more conveniently.
* :heavy_check_mark: You get an alternative to inheritance when dealing with configuration presets for complex objects.
* :x: Cloning complex objects that have circular references might
be very tricky.