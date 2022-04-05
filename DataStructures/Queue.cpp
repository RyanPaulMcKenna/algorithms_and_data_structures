#include <iostream>

using namespace std;

// A Queue has at most n-1 elements. 
class Queue {
    private:
        const int N = 12;
        int tail;
        int head;
        int* Q;
    public:
        Queue()
        {
            head = 1; // set both to first pos.
            tail = 1;
            Q = new int[N] {0};
        }

        int length()
        {
            if (tail > head)
                return (tail-head);
            else if (head > tail)
                return (tail + N - head);
            return 0;
        }

        void Enqueue(int x)
        {
            if (head == tail+1)
                throw std::overflow_error("overflow");

            Q[tail-1] = x;
            if (tail == length())
                tail = 1;
            else
                tail++;
        }
    
        int Dequeue()
        {
            if (head == tail)
                throw std::underflow_error("underflow");

            int x = Q[head-1];
            if (head == length())
                head = 1;
            else
                head++;
            return x;
        }

};



int main()
{
    Queue q;
    q.Enqueue(3);
    q.Enqueue(5);
    q.Dequeue();
    q.Dequeue();
    try {
        q.Dequeue();
    } catch(const std::underflow_error& e)
    {
        std::cout << e.what();
    }

    int x;
    std::cin >> x;
}

