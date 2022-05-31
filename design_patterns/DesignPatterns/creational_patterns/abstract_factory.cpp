class Chair {
    public:
        virtual bool hasLegs() = 0;
        virtual void sitOn() = 0;
}; // Interface
class VictorianChair: public Chair {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
}; /// Concrete class
class ModernChair: public Chair {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
};
class Sofa {
    public:
        virtual bool hasLegs() = 0;
        virtual void sitOn() = 0;
}; // Interface
class VictorianSofa: public Sofa {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
}; /// Concrete class
class ModernSofa: public Sofa {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
};
class CoffeeTable {
    public:
        virtual bool hasLegs() = 0;
        virtual void sitOn() = 0;
}; // Interface
class VictorianCoffeeTable: public CoffeeTable {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
}; /// Concrete class
class ModernCoffeeTable: public CoffeeTable {
    private:
        // ...fields
    public:
        bool hasLegs() {}
        void sitOn() {}
};



class FurnitureFactory {
    public:
        virtual Chair* createChair() = 0;
        virtual CoffeeTable* createCoffeeTable() = 0;
        virtual Sofa* createSofa() = 0;
}; // Interface
class VictorianFurnitureFactory: public FurnitureFactory {
    private:
        // ..fields
    public:
        Chair* createChair() {
            Chair* c = new VictorianChair();
            return c;
        }
        CoffeeTable* createCoffeeTable() {
            CoffeeTable* ct = new VictorianCoffeeTable();
            return ct;
        }
        Sofa* createSofa() {
            Sofa* s = new VictorianSofa();
            return s;
        }
};
class ModernFurnitureFactory: public FurnitureFactory {
    private:
        // ..fields
    public:
        Chair* createChair() {
            Chair* c = new ModernChair();
            return c;
        }
        CoffeeTable* createCoffeeTable() {
            CoffeeTable* ct = new ModernCoffeeTable();
            return ct;
        }
        Sofa* createSofa() {
            Sofa* s = new ModernSofa();
            return s;
        }
}; 

class Client {
    private:
        FurnitureFactory* factory;
    public:
        Client(FurnitureFactory* f): factory{f} {} // Aggregation.
        void orderStock() {
            factory->createChair();
            factory->createSofa();
            factory->createCoffeeTable();   
        }
};

int main() 
{
    // Example 1: class can work with any type of FurnitureFactory
    FurnitureFactory* ff = new VictorianFurnitureFactory();
    Client c(ff);
    c.orderStock();

    // Example 2: Different FurnitureFactory objects can work as one type in an array.
    const size_t countSuppliers = 2;
    FurnitureFactory* supplierA = new VictorianFurnitureFactory();
    /*
    .
    .
    . Various furniture factories 
    */
    FurnitureFactory* supplierB = new ModernFurnitureFactory(); 
    FurnitureFactory* suppliers[countSuppliers] = {supplierA, supplierB};
    for (FurnitureFactory* ff : suppliers)
    {
        ff->createChair();
        ff->createSofa();
        ff->createCoffeeTable();
    }
}