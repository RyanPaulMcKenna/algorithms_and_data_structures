### Builder

**Builder** is a creational design pattern that lets you construct complex objects step by step. The pattern allows you to produce different types and reresentations of an object using the same construction code.

#### Structure
![Builder diagram](/Chapter2/diagrams/Builder.png)

see ***builder.cpp** for implementation.

This Pattern is particularly useful to get rid of huge constructors with many optional paramters.
Calling such a beast is inconvenient.

Whenever you are trying to make very complex objects that are related but are still different things
like Cars and Car Manuals for example, the Builder Pattern pay be a good way to go!

A builder doesn’t expose the unfinished product while running
construction steps. This prevents the client code from fetching
an incomplete result.

#### Pros & Cons
* :heavy_check_mark: You can construct objects step-by-step, defer construction
steps or run steps recursively.
* :heavy_check_mark: You can reuse the same construction code when building various representations of products.
* :heavy_check_mark: Single Responsibility Principle. You can isolate complex construction code from the business logic of the product.
* :x: The overall complexity of the code increases since the pattern
requires creating multiple new classes.

