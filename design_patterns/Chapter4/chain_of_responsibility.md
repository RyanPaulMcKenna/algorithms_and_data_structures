# Chain of Responsibility
*Also known as: CoR, Chain of Command*
**Chain of Responsibility** is a behavioural design pattern that lets you pass requests along a chain of handlers. Upon receiving a request each handler decides either to process the request or to pass it to the next handler in the chain.

### :worried: Problem

You want to restrict access to the system so only certain types of entites can perform certain types of actions. Various check must be performed to ascertain the type of entity and whether it can perform the type of action requested of system. In addition, these checks must be performed sequentially.

*You require many ***"checks"*** against various component types and these checks may be interdependent in a myriad of ways and combinations.*

### :smiley: Solution

*Like many behavioural design pattterns the ***Chain of Responsibility*** relies on transforming particular behaviours into stand-alone objects called handlers.*

You must extract each check to its own class with a single method that performs the check.

The request, along with its data, is passed to this method as an argument.

The pattern suggests that you link these handlers into a chain by storing a field in each hanlder, with a reference to the next handler in the chain.

All handler classes must implement the same interface


#### Structure
![CoF](/Chapter4/diagrams/chain_of_responsibility.png)

*Concrete Handlers are self contained and immutable.*

***Use the Chain of Responsibility pattern when your program is expected to process different kind of requests in various ways, but the exact types of requests and their sequences are unknown beforehand.***


*Lets you control the order of the execution/checks*

#### Pros and Cons

* :heavy_check_mark: You can control the order of request handling.
* :heavy_check_mark: Single Responsibility Principle. You can decouple classes that invoke operations from classes that perform operations.
* :heavy_check_mark: Open/Closed Principle. You can introduce new handlers into the app without breaking the existing client code.
* :x: Some requests may end up unhandled.


