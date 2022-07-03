#include <iostream>

const int MAXSIZE(7);

// Each of the three stack operations take linear time O(1).
class Stack {
    private:
        int top;
        int MAX;
        int* S;
    public:
        Stack()
        {
            top = 0;
            MAX = MAXSIZE;
            S = new int[MAX];
        }
        int Top()
        {
            return top;
        }

        bool StackEmpty()
        {
            if (Top() == 0)
                return true;
            else
                return false;
        }

        void Push(int x)
        {
            top++;
            S[Top()] = x;
        }

        int Pop()
        {
            if (StackEmpty())
                throw std::underflow_error("underflow");
            else {
                top--;
                return S[Top() + 1];
            }

        }
};



int main()
{
    Stack S; // Empty stack with max size of seven by default.
    S.Push(15);
    S.Push(6);
    S.Push(2);
    S.Push(9);
    S.Push(17);
    S.Push(3);
    S.Push(8);

    for (int i = 0; i < MAXSIZE + 100; i++)
    {
        std::cout<< S.Pop() << "\n";
        if (S.StackEmpty())
            break;
    }

    try {
        S.Pop();
    } catch(const std::underflow_error& e)
    {
        std::cout << e.what();
    }

    int x;
    std::cin >> x;


}