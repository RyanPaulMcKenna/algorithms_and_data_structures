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
