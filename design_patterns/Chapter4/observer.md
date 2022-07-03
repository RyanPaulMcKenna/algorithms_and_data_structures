# OBSERVER
*Also known as: Event-Subscriber, Listener*

**Observer** is a behavioral design pattern that lets you define a subscriptions mechanism to notify multiple objects about any events that happen to the object they're observing.

![observer](/Chapter4/diagrams/observer.png)

*A Subscription mechanism lets individual objects subscribe to event notifications.*

*Publisher notifies subscribers by calling the specific notifation method on their objects.*

It is important that all subscribers implment the same interface and that the publisher communicates iwth them only via that interface.

# Structure

![observer](/Chapter4/diagrams/observer_complete.png)

# C++ implementation

```c++
#include <iostream>
#include <string>
#include <vector>

class EventListeners {
    public:
        virtual void update(std::string filename) = 0;
};
class EmailAlertsListener: public EventListeners {
    private:
        // ...
    public:
        void update(std::string filename) {
            std::cout << "Listener: Emailing " << filename << std::endl;
        }
};
class LoggingListener: public EventListeners {
    private:
        // ...
    public:
        void update(std::string filename) {
            std::cout << "Listener: Logging " << filename << std::endl;
        }
};
class Eventmanager {
    private:
        std::vector<EventListeners*> listeners;
    public:
        void subscribe(EventListeners* listener) {
            listeners.push_back(listener);
        }
        void unsubscribe(EventListeners* listener) {
            for (int i = 0; i < listeners.size(); i++) {
                if (listeners[i] == listener) {
                    listeners.erase(listeners.begin() + i);
                }
            }
        }
        void notify(std::string eventType, std::string filename) {
            for (auto listener : listeners) {
                listener->update(filename);
            }
        }
};
class File {
    private:
        std::string name;
        std::string content;
    public:
        File(std::string filename) {
            name = filename;
            content = "";
        }
        void write(std::string content) {
            this->content += content;
        }
        std::string getName() {
            return name;
        }
};
class Editor {
    private:
        File* file;
    public:
        Eventmanager* events;
        Editor(Eventmanager* manager): events{manager}, file{nullptr} {}
        void openFile() {
            std::cout << "Opening file..." << std::endl;
            std::string filename = "example.txt";
            this->file = new File(filename);
            events->notify("open", this->file->getName());
            std::cout << "File opened" << std::endl;
            std::cout << "--------------------------" << std::endl;
        }
        void saveFile() {
            std::cout << "Saving file..." << std::endl;
            this->file->write("Hello World!");
            events->notify("save", this->file->getName());
            std::cout << "File saved" << std::endl;
            std::cout << "--------------------------" << std::endl;
        }
};

int main() {

    Eventmanager* eventmanager = new Eventmanager();
    EventListeners* emailAlertsListener = new EmailAlertsListener();
    EventListeners* loggingListener = new LoggingListener();
    eventmanager->subscribe(emailAlertsListener);
    eventmanager->subscribe(loggingListener);
    Editor editor(eventmanager);

    editor.openFile();
    editor.saveFile();
}
```

## Applicability
Use the Observer pattern when changes to the state of one object may require changing other objects, and the actual set of objects is unknown beforehand or changes dynamically.


## Pros and Cons

* :heavy_check_mark: *Open/Closed Principle.*
* :heavy_check_mark: You can estabilsh relations between objects at runtime.
* :x: Subscribers are notified in random order.

