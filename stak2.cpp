/*
    Да се напише програма, чрез която от клавиатурата се въвежда естествено
    число N от интервала [10.. 100]. Програмата да генерира N броя
    естествени числа от интервала [1.. 101]. Числата да бъдат записани в 
    стек. При извеждането на елементите на стека числата да се разделят
    на четни и нечетни, запазвайки двете групи в отделни стекове. Четните
    трябва да се извеждат в същия ред, както са въвеждани в основния стек,
    а нечетните стойности се извеждат в ред обратен на въвеждането им.
*/
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int NUM = 1000; // Default capacity of stack

template <typename O>
class ArrayStack
{
    public:
        ArrayStack(int cap = NUM); // constructor
        ~ArrayStack();  // destructor
        ArrayStack(const ArrayStack& other); // copy constructor
        ArrayStack& operator=(const ArrayStack& other); // assignment operator

        int getN() { return n; }
        void setN(int val) { n = val; }
        int getT() { return t; }
        void setT(int val) { t = val; }

        void push(const O& obj);
        O pop();

        O& top() const
        { return arr[t]; }

        bool isEmpty() const
        { return (t < 0); }

        int size() const
        { return (t + 1); }

        void print();

    protected:

    private:
        int n; // The length of stack array
        O* arr; // The stack array
        int t; // Index of the top of the stack
};

template <typename O>
ArrayStack<O>::ArrayStack(int cap)
{
    n = cap;
    arr = new O[n];
    t = -1;
}

template <typename O>
ArrayStack<O>::~ArrayStack()
{
    delete [] arr;
}

template <typename O>
ArrayStack<O>::ArrayStack(const ArrayStack& other)
{
    n  = other.n;
    t = other.t;
    arr = new O[n];

    // copy contents
    for (int i = 0; i <= t; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename O>
ArrayStack<O>& ArrayStack<O>::operator=(const ArrayStack& rhs)
{
    if (this != &rhs) {			// avoid self copy (x = x)
        delete [] arr;			// delete old contents
        n = rhs.n;
        t = rhs.t;
        arr = new O[n];

        // copy contents
        for (int i = 0; i <= t; i++) {
            arr[i] = rhs.arr[i];
        }
  }

  return *this;
}

template <typename O>
void ArrayStack<O>::push(const O& obj)
{
    if (size() == n)
    {
        cout<<"Stack overflow"<<endl;
        return;
    }

    t++;
    arr[t] = obj;
}

template <typename O>
O ArrayStack<O>::pop()
{
    if (isEmpty())
    {
        cout<<"Access to empty stack"<<endl;
        return 1;
    }

    return arr[t--];
}

template <typename O>
void ArrayStack<O>::print()
{
    while(!isEmpty())
    {
        cout << top() << " ";
        pop();
    }
    cout << endl;
}

template <typename O>
ArrayStack<O> reversSteck (ArrayStack<O> temp) {
      ArrayStack<O> revSteck;

      while(!temp.isEmpty()) {
            revSteck.push(temp.top());
            temp.pop();
    }
    return revSteck;
}

int main()
{
    ArrayStack<int> st;

    ArrayStack<int> odd_numb; // Odd numbers
    ArrayStack<int> even_numb; // Even numbers
    ArrayStack<int> temp;

    int N, num;
    time_t t;// Take the current time

    srand( time(&t));// Initializes a random number generator

    cout<<"Enter integer number between 10 and 100: ";
    cin>>N;

    cout<<"Generating "<<N<<" pseudo random numbers:\n";
    for (int i=1; i<=N; i++){
        num=1+rand()%101;
        cout<<num<<" ";

        st.push(num);
    }
    cout<<"\n";

    cout<<"The top on original stack is: "<<st.top();
    cout<<endl;
    int x;
    for(int i=1;i<=N;i++){
        x = st.top();
        if (x%2 == 0) {
            even_numb.push(x);
        }
        else {
            temp.push(x);
        }
        st.pop();
    }

    odd_numb = reversSteck(temp);
    cout<<"\n";

    cout<<"The top of stack with odd numbers is: "<<odd_numb.top()<<"\n";
    cout<<"Odd numbers: ";
    odd_numb.print();
    cout<<endl;

    cout<<"The top of stack with even numbers is: "<<even_numb.top()<<"\n";
    cout<<"Even numbers: ";
    even_numb.print();
    cout<<endl;

    system("PAUSE");
    return 0;
}
