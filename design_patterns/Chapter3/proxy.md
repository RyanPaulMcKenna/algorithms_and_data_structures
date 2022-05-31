# PROXY

**Proxy** is a structural design pattern that lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perfrom something either before or after the request gets through to the original object.

### :worried: Problem

Imagine that you have a massive object that consumes a vast amount of system resources. You need it from time to time, but not always.

*Database for example*

### :smiley: Solution

The Proxy pattern suggests that you create a new proxy class with the same interface as the original service object.

Then this object can be passed around instead of the original service. Upon receiving a request the proxy creates a real service object and delegates all the work to it.

***Example***
*The proxy disguises itself as a database object. It can handle lazy initalization and result caching without the client or the real database object even knowing.*

```c++
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

```

### Structure

![proxy](/Chapter3/diagrams/proxy.png)


The Proxy usually manages the full lifecycle of their service objects.
The Proxy is responsible for processing such as; lazy-initalization, logging, access control, caching, etc.

#### Applicability

* Lazy initalization, when you have heavyweight service object that wastes system resources by being always up.

* Access control (protection proxy) A barrier to only provide specific clients with access to the service object. The client's credentials will need to pass some criteria.


* Logging requests (Logging proxy). This when you want to keep a history of requests to the service object.

* Caching requests (Caching proxy). This is when you want to cache results of client requests and manage lifecycle of this cache. Especially if results are quite large.

