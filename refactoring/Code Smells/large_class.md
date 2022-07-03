# Large Class
A class contains many fields/methods/lines of code.

**Reasons for the Problem**
Classes usually start small. But over time, they get bloated as the program grows.

As is the case with long methods as well, programmers usually find it mentally less taxing to place a new feature in an existing class that to create a new class for the feature.

**Treatment**
When a class is wearing to many (functional) hats, think about splitting it up.

# Recipe #1: Extract Class
**Extract Class** helps if part of the behavior of the large class can be spun off into a separate component.

## :x: Problem
When one class does the work of two, awkwardness results.
```c++
class Person {
    private:
        string name;
        string officeAreaCode;
        string officeNumber;
    public:
        string getTelephoneNumber() {
            // ...
        }
}
```

## :heavy_check_mark: Solution
Instead, create a new class and place the fields and methods responsible for the relevant functionality in it.
```c++
class TelephoneNumber {
    private:
        string officeAreaCode;
        string officeNumber;
    public:
        string getTelephoneNumber() {
            // ...
        }
};
class Person {
    private:
        string name;
        TelephoneNumber myNum;
    public:
        Person() {}
        Person(TelephoneNumber t) {
            myNum = t;
        }
        void setTelephoneNumber(TelephoneNumber t)
        {
            myNum = t;
        }
        string getTelephoneNumber() {
            return t.getTelephoneNumber();
        }
};
```


# Recipe #2: Extract Subclass
**Extract Subclass** helps if part of the behavior of the large class can be implemented in  different ways or is used in rare cases.

## :x: Problem
A class has features that are used only in certain cases.
```c++
class JobItem {
    private:
        // ...
    public:
        double getTotalPrice();
        double getUnitPrice();
        Employee getEmployee();
}
```

## :heavy_check_mark: Solution
Create a subclass and use it in these cases.
```c++
class JobItem {
    private:
        // ...
    public:
        virtual double getTotalPrice() {
            // ...
        }
        virtual double getUnitPrice() {
            // ...
        }
        virtual Employee getEmployee() {
            // ...
        }   
};
class LaborItem : public JobItem {
    public:
        double getUnitPrice() {
            // override.
        }
        Employee getEmployee() {
            //override.
        }
};
```


# Recipe #3: Extract Interface
**Extract Interface** helps if it's necessary to have a list of the operations and behaviors that the client can use.

## :x: Problem
Multiple clients are using the same part of a class interface. Another case: part of the interface in two classes is the same.
```c++
class Employee {
    private:
        // ...
    public:
        double getRate();
        bool hasSpecialSkill();
        char* getName();
        char* getDepartment();
};
```


## :heavy_check_mark: Solution
Move this idential portion to its own interface.
```c++
class Billable {
    public:
        virtual double getRate() = 0;
        virtual bool hasSpecialSkill() = 0;
};
class Employee : public Billable {
    public:
        double getRate();
        bool hasSpecialSkill();
        char* getName();
        char* getDepartment();
};
```


# Recipe #4: Separate GUI and Domain Data
If a large class is responsible for the graphical interface, you may try to move some of its data and behavior to a separate domain object. In doing so, it may be necessary to store copies of some data into place and keeep the data consistent. **Duplicate Oserved Data** offers a way to do this.

**Duplicate Observed Data**

## :x: Problem
Is domain data stored in classes responsible for the GUI?
```c++
class TextField;
class IntervalWindow {
    private:
        TextField startField;
        TextField endField;
        TextField lengthField;
    public:
        void StartField_FocusLost();
        void EndField_FocusLost();
        void LengthField_FocusLost();
        void calculateLength();
        void calculateEnd();
};
```


## :heavy_check_mark: Solution
Then it's a good idea to separate the data into separate classes, ensuring connection and synchronization between the domain class and the GUI.
```c++
class TextField;
class IntervalWindow {
    private:
        TextField startField;
        TextField endField;
        TextField lengthField;
    public:
        void StartField_FocusLost();
        void EndField_FocusLost();
        void LengthField_FocusLost();
};
class Interval {
    private:
        string start;
        start end;
        string length;
    public:
        void calculateLength();
        void calculateEnd();
};
```

## Payoff
:green_heart: ***Refactoring of these classes spares developers from needing to remember a large number of attributes for a class.***
:green_heart: ***In many cases, splitting large classes into parts avoids duplication of code and functionality.***
