/*
    Да се напише програма, която създава и извежда опашка от опашки от цели
    числа.
*/

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int const size = 1000;

template <typename T>
class Queue{
      public:
            Queue(); // Constructor
            ~Queue(); // Destructor
            Queue(Queue const &); // Copy constructor
            Queue& operator=(Queue const &); // Operator Assignment
            void InsertElem(T const &); // Insert element into the queue
            int DeleteElem(T &); // Delete element from queue
            void print(); // Print queue
            T front()
            {
                if (isEmpty())
                {
                    cout<<"Access to empty queue!"<<endl;
                    return 1;
                }

                return queueArr[f];
            }
            bool isEmpty() const
            { return (n == 0); }
            int queueSize() const
            { return (n); }
      private:
            int f, rear, n;
            T *queueArr;
            void copyQueue(Queue const &); // Copy queue
};

/* Constructor
   n     - Number of items in the queue
   f     - The index of the first item in the queue
   rear  - The index of the last item in the queue
*/
template <typename T>
Queue<T>::Queue() {
      queueArr = new T[size];
      n = 0;
      f = 0;
      rear = 0;
}

// Destructor
template <typename T>
Queue<T>::~Queue(){
      delete [] queueArr;
}

// Copy constructor
template <typename T>
Queue<T>::Queue(Queue<T> const& r) {
      copyQueue(r);
}

// Operator Assignment
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T> const& r) {
      if (this != &r){
            delete [] queueArr;
            copyQueue(r);
      }

      return *this;
}

// Insert element into the queue
template <typename T>
void Queue<T>::InsertElem(T const &x) {
      if (n == size)
      {
          cout << "Impossible! \n";
      }
      else {
            queueArr[rear] = x;
            n++;
            rear++;
            rear = rear % size;
      }
}

// Delete element from queue
template <typename T>
int Queue<T>::DeleteElem(T &x) {
      if (n > 0) {
            x = queueArr[f];
            n--;
            f++;
            f = f % size;
            return 1;
      }
      else return 0;
}

// Copy queue
template <typename T>
void Queue<T>::copyQueue(Queue<T> const &r) {
      queueArr = new T[size];

      for (int i = 0; i < size; i++)
            queueArr[i] = r.queueArr[i];

      n = r.n;
      f = r.f;
      rear = r.rear;
}

// Print queue
template <typename T>
void Queue<T>::print(){
      T x;
      while (DeleteElem(x))
            cout << x << " ";
cout << endl;
}

int main()
{
    time_t t;// Take the current time

    srand( time(&t));// Initializes a random number generator

    Queue< Queue<int> > mainQueue;

    for (int i = 1; i <= 5; i++)
    {
        Queue<int> tmp;
        for (int i = 1; i <= 10; i++)
            tmp.InsertElem((1+rand()%101));

        mainQueue.InsertElem(tmp);
    }

    Queue<int> q;
    for (int i = 1; i <= 5; i++)
    {
        mainQueue.DeleteElem(q);
        q.print();
    }
    return 0;
}
