#include <iostream>

using namespace std;


// Needs to be tested.
// A Deque
class Deque {
    private:
        const int N = 12;
        int tail;
        int head;
        int* Q;
    public:
        Deque()
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

        void EnqueueFront(int x) // Queue
        {
            if (head == tail+1)
                throw std::overflow_error("overflow");

            Q[tail-1] = x;
            if (tail == length())
                tail = 1;
            else
                tail++;
        }

        void EnqueueBack(int x) // Deque
        {
            Q[head-2] = x;
            if ((head-1) == 1)
                head = length();
            else
                head--;
        }
            
        int DequeueFront() // Deque
        {
            if (head == tail)
                throw std::underflow_error("underflow");

            int x = Q[tail-2];
            if ((tail-1) == 1)
                tail = length();
            else
                tail--;
            return x;
        }    
    
        int DequeueBack() // Queue
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
    Deque q;
    q.EnqueueFront(1);
    q.EnqueueFront(2);
    q.EnqueueBack(3);
    q.EnqueueBack(4);

    cout << q.DequeueBack() << endl;
    cout << q.DequeueBack() << endl;
    cout << q.DequeueBack() << endl;
    cout << q.DequeueBack() << endl;


    int x;
    std::cin >> x;
}

