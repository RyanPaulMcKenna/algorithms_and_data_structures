# ITERATOR

**Iterator** is a behavioral design pattern that lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).

## :worried: Problem

Collections can be storied in lists, trees, stacks and many other structures.
Common to all of these is the need to access the elements of the collection.

*The same collection can be traversed in many different way; BFS, DFS, Random access, etc.*

Adding more and more traversal algorithms to the collection gradually blurs its primary responsibility. Which is efficient data storage.

## :smiley: Solution

The Iterator pattern suggests extracting the traveersal behaviour of a collection into a seperate object called an iterator.

### Structure

```c++
#include <iostream>
#include <string>
#define SIZE 4


// ABSTRACT CLASSES
class Iterator {
    public:
        virtual bool hasNext() = 0;
        virtual std::string* getNext() = 0;
};

class Container {
   public: 
    virtual Iterator* getIterator() = 0;
};
// CONCRETE CLASSES
class NameIterator: public Iterator {
    private:
        int index;
        std::string* names;
    public:
        NameIterator(std::string* names) {
            this->names = names;
            index = 0;
        }
        bool hasNext();
        std::string* getNext();
};

class NameRepository: public Container {
   Iterator* nameIter;
   public:
    NameRepository(): nameIter(nullptr) {}
    std::string names[SIZE] = {"Robert" , "John" ,"Julie" , "Lora"};


   Iterator* getIterator() {
      nameIter = new NameIterator(names);
      return nameIter;
   }

   private: 

};

bool NameIterator::hasNext() {
    if(index < SIZE) {
        return true;
    }
    return false;
}

std::string* NameIterator::getNext() {
    if(hasNext()){
        return &names[index++];
    }
    return nullptr;
}	

// USAGE

int main() {
      NameRepository* namesRepository = new NameRepository();

      for(Iterator* iter = namesRepository->getIterator(); iter->hasNext(); ){
         std::string name = (std::string)*iter->getNext();
         std::cout << "Name: " << name << std::endl;
      }
}
```

# Applicability

* Use the iterator pattern when your collection has a complex data structure under the hood, but you want to hide its complexity from clients (For convenience or security).

* Could be used for iterating through trees or graphs or even more convoluted data structures.

## Pros and Cons

* *Single Responsibility Principl*
* *Open/Closed Principle*
* Parallelizable, because each iterator contains its own state.
* Overkill for simple collections like the example above.
* Can be less performant than the direct approach.

