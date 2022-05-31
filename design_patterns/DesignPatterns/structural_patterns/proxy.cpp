class ServiceInterface {
    public:
        virtual void operation() = 0;
}; // Interface

class Service: public ServiceInterface {
    private:
        // ...many fields
    public:
        // ...many methods
        void operation() override {}
}; // Real service.

class Proxy: public ServiceInterface {
    private:
        Service* service;
    public:
        Proxy(Service* s): service{s} {} // Aggregation.
        bool checkAccess() {
            // ...
            return true;
        }
        void operation() override {
            if (checkAccess()) {
                service->operation();
            }
        }
}; // Proxy Service.

class Client {
    public:
        void run() {
            ServiceInterface* service = new Proxy(new Service());
            service->operation();
        }
}; // Client.