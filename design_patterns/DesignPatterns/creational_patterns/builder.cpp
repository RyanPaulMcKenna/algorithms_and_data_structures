
class Engine {

}; // Interface
class SportsEngine: public Engine {

}; // Concrete
class SUVEngine: public Engine {

}; // Concrete

class TripComputer {

}; // Interface
class GenericTripComputer: public TripComputer {

}; // Concrete
class GPS {

}; // Interface
class GenericGPS: public GPS {

}; // Concrete

class Car {
    private:
        size_t seats;
        Engine engine;
        TripComputer tripComputer;
        GPS gps;
    public:
        void setSeats(size_t seats) {
            this->seats = seats;
        }
        void setEngine(Engine engine) {
            this->engine = engine;
        }
        void setTripComputer(TripComputer tripComputer) {
            this->tripComputer = tripComputer;
        }
        void setGPS(GPS gps) {
            this->gps = gps;
        }
};

class Manual {
    private:
        size_t seats;
        Engine engine;
        TripComputer tripComputer;
        GPS gps;
    public:
        void setSeats(size_t seats) {
            this->seats = seats;
        }
        void setEngine(Engine engine) {
            this->engine = engine;
        }
        void setTripComputer(TripComputer tripComputer) {
            this->tripComputer = tripComputer;
        }
        void setGPS(GPS gps) {
            this->gps = gps;
        }
};

class Builder {
    public:
        virtual void reset() = 0;
        virtual void setSeats(size_t seats) = 0;
        virtual void setEngine(Engine engine) = 0;
        virtual void setTripComputer(TripComputer computer) = 0;
        virtual void setGPS(GPS navigation) = 0;
};

class CarBuilder: public Builder {
    private:
        Car* car;
    public:
        void reset() {
            delete car;
            car = new Car();
        }
        void setSeats(size_t seats) {
            car->setSeats(seats);
        }
        void setEngine(Engine e) {
            car->setEngine(e);
        }
        void setTripComputer(TripComputer c) {
            car->setTripComputer(c);
        }
        void setGPS(GPS g) {
            car->setGPS(g);
        }
        Car getResult() {
            return *car;
        }
};

class CarManualBuilder: public Builder {
    private:
        Manual* manual;
    public:
        void reset() {
            delete manual;
            manual = new Manual();
        }
        void setSeats(size_t seats) {
            manual->setSeats(seats);
        }
        void setEngine(Engine e) {
            manual->setEngine(e);
        }
        void setTripComputer(TripComputer c) {
            manual->setTripComputer(c);
        }
        void setGPS(GPS g) {
            manual->setGPS(g);
        }
        Manual getResult() { 
            // ideally getResult should be a standard name for every subclass of builder
            return *manual;
        }
};

class Director {
    private:
    // ...
    public:
        void makeSUV(Builder *builder) {
            builder->reset();
            builder->setSeats(4);
            builder->setEngine(SUVEngine());
            builder->setTripComputer(GenericTripComputer());
            builder->setGPS(GenericGPS());
        }
        void makeSportsCar(Builder *builder) {
            builder->reset();
            builder->setSeats(2);
            builder->setEngine(SportsEngine());
            builder->setTripComputer(GenericTripComputer());
            builder->setGPS(GenericGPS());
        }
};

class Client {
    public:
        void test() {
            Director director;

            // Create a sports car and then a sports car manual
            CarBuilder* carBuilder =  new CarBuilder();
            director.makeSportsCar(carBuilder);
            Car sportsCar = carBuilder->getResult();

            CarManualBuilder* carManualBuilder = new CarManualBuilder();
            director.makeSportsCar(carManualBuilder);
            Manual sportsCarManual = carManualBuilder->getResult();
        }
};

/*
        The example of step-by-step construction of cars and the user guides that
        fit those car models.


        A car is a complex object that can be constructed in a hundred
        different ways. Instead of bloating the Car class with a huge
        constructor, we extracted the car assembly code into a separate car builder class.
        This class has a set of methods for configuring various parts of a car
*/