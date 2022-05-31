# Singleton

**Singleton** is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.


##### :worried: Problem
The singleton pattern solves two problems at the same time, violating the *Single Responsibility Principle:*

1. **Ensure that a class has just a single instance**

2. **Provide a global access point to that instance**

##### :smiley: Solution

* Make default constructor private, to prevent other objects from using the ***new*** operator with the Singleton class.

* Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static field. All following calls to this method return the cached object.

#### Structure

![Singleton](/Chapter2/diagrams/singleton.png)

#### Applicability

* **Use the Singleton pattern when a class in your program should have just a single instance available to all clients; for example, a single databse object shared by different parts of the program**

* **Use the Singleton Pattern when you need stricter control over global variables.**

#### Pros & Cons
* :heavy_check_mark: You can be sure that a class has only a single instance.
* :heavy_check_mark: You gain a global access point to that instance.
* :heavy_check_mark: The singleton object is initialized only when it’s requested for
the first time.
* :x: Violates the *Single Responsibility Principle*. The pattern solves
two problems at the time.
* :x: The Singleton pattern can mask bad design, for instance, when
the components of the program know too much about
each other.

* :x: The pattern requires special treatment in a multithreaded
environment so that multiple threads won’t create a singleton
object several times.
* :x: It may be difficult to unit test the client code of the Singleton because many test frameworks rely on inheritance when
producing mock objects. Since the constructor of the singleton
class is private and overriding static methods is impossible in
most languages, you will need to think of a creative way to
mock the singleton. Or just don’t write the tests. Or don’t use
the Singleton pattern.