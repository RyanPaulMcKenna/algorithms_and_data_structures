# COMMAND
*Also known as: Action, Transaction*

**Command** is a behavioural design pattern that truns a request into a stand-alone object that contains all information about the request. This transformation lets you pass requets as method arguments, delay or queue a request's ececution, and support undoable operations.

### :worried: Problem
In the context of GUI application, lots of different objects with the same or similar behaviour are causing a proliferation of subclasses driven by GUI code becoming awkwardly dependent on the volatile code of the business logic.

### :smiley: Solution


The command pattern suggests that the GUI objects shouldn't send their requests directly to the business logic. Instead you should extract all of the request details, such as the object being call, the name of the method and the list of arugments into a separate *Command* class with a single method that triggers this request.

Command objects serve as links between various GUI and business logic objects. From now on, the GUI object doesn't need to know what business logic object will receive the request or how it'll be processed.

The GUI just triggers the command, which handles the details.

![command](/Chapter4/diagrams/command.png)

*The GUI objects delegate the work to commands.*

### C++ Implementation

```c++
class Command {
    public:
        virtual void execute() = 0;
}; // Interface
class SaveCommand: public Command {
    void execute() override {
        // Save
    }
};
class OpenCommand: public Command {
    void execute() override {
        // Open
    }
};
class PrintCommand: public Command {
    void execute() override {
        // Print
    }
};

class Button  {
    private:
        Command *command;
    public:
        Button(Command *command) {
            this->command = command;
        }
        void click() {
            command->execute();
        }
};

class Shortcut {
    private:
        Command *command;
    public:
        Shortcut(Command *command) {
            this->command = command;
        }
        void press() {
            command->execute();
        }
};

```

*This pattern is all about seperation of concerns*

For example seperating business logic from GUI logic. Otherwise the GUI would have tons of element subclasses even for the same types of GUI elements to accomodate different business logic behaviours.

Command pattern allows us to separate the two completely. GUI elements don't need to know anything about the business logic they just execute the Commands they are given and all those command subclasses are part of the business logic. *Single Responsibility Principle.*

You can introduce new commands without breaking any existing code and the business logic is encapsulated from the GUI *Open/Closed Principle*.

#### Applicability

Use the command pattern when you want to implement reversible operations.

Deferred execution opertions.