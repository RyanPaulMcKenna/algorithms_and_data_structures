# Recipe #1: Extract Method
To reduce the length of a method body, use **Extract Method**.

## :x: Problem
You have a code fragment that can be grouped together.
```c++
void printOwing() {
  printBanner();

  // Print details.
  System.out.println("name: " + name);
  System.out.println("amount: " + getOutstanding());
}
```


## :heavy_check_mark: Solution
Move this code to a separate new method (or function) and replace the old code with a call to the method.
```c++
void printOwing() {
  printBanner();
  printDetails(getOutstanding());
}
void printDetails(double outstanding) {
  // Print details.
  System.out.println("name: " + name);
  System.out.println("amount: " + outstanding);
}
```

# Recipe #2: Reduce Local Variables and Parameter Before Extracting a Method
If local variables and parameters interfere with extracting a method, use **Replace Temp with Query, Introduce Parameter Object** or **Preserve Whole Object**.

* **Replace Temp with Query**

## :x: Problem
You place the result of an expression in a local variable for later use in your code.
```c++
double calculateTotal() {
  double basePrice = quantity * itemPrice;
  if (basePrice > 1000) {
    return basePrice * 0.95;
  }
  else {
    return basePrice * 0.98;
  }
}
```

## :heavy_check_mark: Solution
Move the entire expression to a separate metho and return the result from it. Query the method instead of using a variable. Incorporate the new method in other methods, if necessary.
```c++
double basePrice() {
  return quantity * itemPrice;
}
double calculateTotal() {
  if (basePrice() > 1000) {
    return basePrice() * 0.95;
  }
  else {
    return basePrice() * 0.98;
  }
}
```

* **Introduce Parameter Object**

## :x: Problem
Your methods contain a repeating groups of parameters.
```c++
class Customer {
  public:
    amountInvoicedIn(Date start, Date end) {}
    amountReceivedIn(Date start, Date end) {}
    amountOverdueIn(Date start, Date end) {}
};
```

## :heavy_check_mark: Solution
Replace these parameters with an object.
```c++
class Customer {
  public:
    amountInvoicedIn(Date dateRange) {}
    amountReceivedIn(Date dateRange) {}
    amountOverdueIn(Date dateRange) {}
};
```

* **Preserve Whole Object**

## :x: Problem
You get several values from an object and then pass them as parameters to a method.
```c++
int low = daysTempRange.getLow();
int high = daysTempRange.getHigh();
bool withinPlan = plan.withinRange(low,high);
```


## :heavy_check_mark: Solution
Instead, try passing the whole object.
```c++
bool withinPlan = plan.withinRange(daysTempRange);
```


# Recipe #3: Replace Method with Method Object
If none of the previous recipes help, try moving the entire method to a separate object via 

**Replace Method with Method Object**.
If none of the previous recipes help, try moving the entire method to a seperate object via **Replace Method with Method Object**.

## :x: Problem
You have a long method in which the local variables are so intertwined that you can't apply *Extract Method*.
```c++
class Order {
  // ...
  public:
    double price() {
      double primaryBasePrice;
      double secondaryBasePrice;
      double tertiaryBasePrice;
      // Perform long computation.
    }
}
```

## :heavy_check_mark: Solution
Transform the method into a separate class so that the local variables become fields of the class. Then you can split the method into several methods within the same class.
```c++
class PriceCalculator {}
class Order {
  double price() {
    return new PriceCalculator(this).compute();
  }
};
class PriceCalculator {
  private:
      double primaryBasePrice;
      double secondaryBasePrice;
      double tertiaryBasePrice;
  public:
    PriceCalculator(Order order) {
      // copy relevant information from the
      // order object.
    }
    double compute() {
      // Perform long computation.
    }

};
```

# Recipe #4: Conditonals and Loops
Conditional operators and loops are a good clue that code can be move to a separate method. For conditonals, use **Decompose Conditional**. If loops are in the way, try **Extract Method**.

* **Decompose Conditional**

## :x: Problem
You have a complex conditonal.
```c++
if (date.before(SUMMER_START) || date.after(SUMMER_END)) {
  charge = quantity * winterRate + winterServiceCharge;
}
else {
  charge = quantity * summerRate;
}
```

## :heavy_check_mark: Solution
Decompose the complicated parts of the conditional into separate methods: the condition, **then** and **else**.
```c++
if (isSummer(date)) {
  charge = summerCharge(quantity);
} else {
  charge = winterCharge(quantity);
}
```

* **Extract Method**

## :x: Problem
You have a code fragment that can be grouped together.
```java
void printProperties(List users) {
  for (int i = 0; i < users.size(); i++) {
    String result = "";
    result += users.get(i).getName();
    result += " ";
    result += users.get(i).getAge();
    System.out.println(result);

    // ...
  }
}
```

## :heavy_check_mark: Solution
Move this code to a seprate new method (or function) and replace the old code with a call to the method.

```java
void printProperties(List users) {
  for (User user : users) {
      System.out.println(getProperties(user));
  
    // ...
  }
}

String getProperties(User user) {
  return user.getName() + " " + user.getAge();
}
```

## Payoff
:green_heart:  ***Among all types of object-orientated code, classes with short methods live longest. The longer a method or function is, the harder it becomes to understand and maintain it.***

:green_heart: ***In addition, long methods offer the perfect hiding place for unwanted duplicate code.***

## A Few Words on Performance
Does an increase in the number of methods hurt performance, as many people claim? In almost all cases the impact is so negligible that it's not even worth worrying about.

Plus, now that you have clear and understandable code, your're more likely to find truly effective method for restructuring code and getting real performance gains if the need ever arises.
