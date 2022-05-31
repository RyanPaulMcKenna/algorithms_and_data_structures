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

int main() {
    Notifier* notifier = new SMSDecorator(new FacebookDecorator(new SlackDecorator(new EmailNotifier())));
    notifier->send("Hello World!");
    return 0;
}