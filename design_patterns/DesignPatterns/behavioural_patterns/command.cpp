// GUI EXAMPLE.

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

// Kitchen EXAMPLE.
class Order {
    public:
        virtual void execute() = 0;
};
class Pasta: public Order {
    void execute() override {
        // Make pasta.
    }
};
class PizzaSpecialist {
    public:
        void action(int topping) {
            // Action
        }
};
class Pizza: public Order {
    private:
        PizzaSpecialist *receiver;
        int topping;
    public:
        Pizza(PizzaSpecialist *receiver, int topping) {
            this->receiver = receiver;
            this->topping = topping;
        }
        void execute() override {
            receiver->action(topping);
            // Make pizza.
        }
};


class Chef {
    private:
        Order *order;
    public:
        Chef(Order *order) {
            this->order = order;
        }
        void setOrder(Order *order) {
            this->order = order;
        }
        void cook() {
            order->execute();
        }
};


class Waiter {
    public:
        Waiter() {}
        void takeOrder(Order *order, Chef* chef) {
            chef->setOrder(order);
            chef->cook();
        }
};

class Client {
    public:
        void main() {
            enum toppings { pepperoni, mushrooms, onions, cheese };
            Waiter *waiter = new Waiter();
            Chef *chef = new Chef(new Pasta()); // default is pasta.
            Order* order = new Pizza(new PizzaSpecialist(), toppings::pepperoni);
            waiter->takeOrder(order, chef);
        }
};

int main() {
    Client client;
    client.main();
}