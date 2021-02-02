/*
    Да се напише програма, която извежда двоично
    представяне на естествено число.
*/

#include <iostream>

using namespace std;

const int NUM = 1000; // Default capacity of stack

template <typename O>
class ArrayStack {
    private:
       int n; // The length of stack array
       O* arr; //The stack array
       int t; // Index of the top of the stack

    public:
       ArrayStack(int cap = NUM)
       {
           n = cap;
           arr = new O[n];
           t = -1;
       }

       ArrayStack(const ArrayStack& st);   // copy constructor
       ArrayStack& operator=(const ArrayStack& st); // assignment operator

       // destructor
       ~ArrayStack()
       { delete [] arr; }

       void push(const O& obj)
       {
           if (size() == n)
           {
               cout<<"Stack overflow"<<endl;
               return;
           }

           t++;
           arr[t] = obj;
       }

       O pop()
       {
           if (isEmpty())
           {
               cout<<"Access to empty stack"<<endl;
               return 1;
           }
           return arr[t--];
       }

       O& top() const
       { return arr[t]; }

       bool isEmpty() const
       { return (t < 0); }

       int size() const
       { return (t + 1); }

       void print()
       {
           while(!isEmpty()){
               cout<<top();
               pop();
           }
           cout << endl;
       }

};

// copy constructor
template <typename O>
ArrayStack<O>& ArrayStack<O>::operator=(const ArrayStack& st) {
    if (this != &st) {    // avoid self copy (x = x)
       delete [] arr;   // delete old contents
       n = st.n;
       t = st.t;
       arr = new O[n];

       // copy contents
       for (int i = 0; i <= t; i++) {
           arr[i] = st.arr[i];
       }
    }
    return *this;
}

int main()
{
    int n;

    cout << "Enter integer number > 0: ";
    cin >> n;

    ArrayStack<int> st;

    while(n) {
        st.push(n % 2);
        n /= 2;
    }

    st.print();

    return 0;
}
