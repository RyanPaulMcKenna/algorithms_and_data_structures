# DECORATOR
*Also known as: Wrapper*

**Decorator** is a structural design pattern that lets you arrach new behaviours to objects by placing these objects inside special wrapper objects that contain the behaviours.


***Think Russian Doll***

### :worried: Problem
Suffering from explosion of subclasses in inheritance hierarchy.


### :smiley: Solution
* Beware, inheritance is static: you can't alter the behaviour of an existing object at runtime.

* Subclasses can have just one parent class in most languages. 

One of the ways to overcome these caveats is by using Aggregation or Composition instead of inheritance.

*Aggregation/composition is the key principle behind many design patterns*


![Decorator pattern](/Chapter3/diagrams/decorator.png)

*Various notification methods become decorators.*

#### C++ Example of Decorator pattern.

```c++
#include <iostream>
#include <string>

class Notifier {
public:
    virtual void send(std::string message) = 0;
}; // Interface.


class EmailNotifier: public Notifier {
    public:
        void send(std::string message) {
            std::cout << "Sending Email: " << message << std::endl;
        }
}; // Concrete class.

class BaseDecorator : public Notifier { // Implements Interface.
    private:
        Notifier* wrappee; // Aggregated.
    public:
        BaseDecorator(Notifier* notifier): wrappee(notifier) {}
        void send(std::string message) {
            wrappee->send(message);
        }
};

class SMSDecorator : public BaseDecorator {
    private:
        void sendSMS(std::string message) {
            std::cout << "Sending SMS: " << message << std::endl;
        }
    public:
        SMSDecorator(Notifier* notifier): BaseDecorator(notifier) {}
        void send(std::string message) {
            BaseDecorator::send(message);
            sendSMS(message);
        }
};

class FacebookDecorator : public BaseDecorator {
    private:
        void sendFacebook(std::string message) {
            std::cout << "Sending Facebook: " << message << std::endl;
        }
    public:
        FacebookDecorator(Notifier* notifier): BaseDecorator(notifier) {}
        void send(std::string message) {
            BaseDecorator::send(message);
            sendFacebook(message);
        }
};

class SlackDecorator : public BaseDecorator {
    private:
        void sendSlack(std::string message) {
            std::cout << "Sending Slack: " << message << std::endl;
        }
    public:
        SlackDecorator(Notifier* notifier): BaseDecorator(notifier) {}
        void send(std::string message) {
            BaseDecorator::send(message);
            sendSlack(message);
        }
};

class Application {
    private:
        Notifier* notifier;
        bool facebookEnabled;
        bool SlackEnabled;
        bool SMSEnabled;
    public:
        Application(bool fb, bool sl, bool sms) {
            facebookEnabled = fb;
            SlackEnabled = sl;
            SMSEnabled = sms;
        }
        void setNotifier(Notifier* notifier) {
            this->notifier = notifier;
        }
        void configure() {
            Notifier stack = new EmailNotifier();
            if (facebookEnabled)
            {
                stack = new FacebookDecorator(stack);
            }
            if (slackEnabled)
            {
                stack = new SlackDecorator(stack);
            }
            if (SMSEnabled)
            {
                stack = new SMSDecorator(stack);
            }
            this->setNotifier(stack);
        }
        void send(std::string message) {
            if (notifier != nullptr) {
                notifier->send(message);
            }
        }
}

int main() {
    Application app(true, true, true);
    app.configure();
    app.send("Hello World!");
}
```

*This allow you to create complex stacks of notification decorators*

#### Another example
![encryption compression](/Chapter3/diagrams/decorator_encryption_compression.png)

#### Applicability

* Use the Decorator pattern when you need to be able to assign extra behaviors to objects at runtime without breaking the code that uses these objects.

* Use the pattern when it’s awkward or not possible to extend an object’s behavior using inheritance.

* When you need **recursive composition**

#### Relations with Other Patterns

Adapter changes the interface of an existing object, while Decorator enhances an object without changing its interface. In addition, Decorator supports recursive composition, which isn’t possible when you use Adapter.

***Decorator lets you change the skin of an object, while Strategy lets you change the guts.***