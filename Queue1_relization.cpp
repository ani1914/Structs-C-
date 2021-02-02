//Реализацията на приоритетна опашка P трябва да осигури следните функции:
//◦ size()–ВръщаброянаелементитевP.
//◦ empty() – Връща true, ако P е празна и false, в противен случай.
//◦ insert(e)–ВмъквановелементeвP.
//◦ min() – Връща референция към елементът от P с най-малкият ключ (но не го премахва).
//◦ removeMin()–ПремахваотPелемента,посоченотmin().
#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <string>

using namespace std;

template<class T>
class LexCompare
{
    public:
        int operator()(const T& a, const T& b) const
        {
            return a < b;
        }
};

template<class E, template<class> class C >
class ListPriorityQueue
{
    public:
        int size() const;
        bool empty() const;
        void insert(const E& e);
        const E& min() const;
        void removeMin();
        void print();
    public:
        list<E> L;
        C<E> isLess;
};

template<class E, template<class> class C >
int ListPriorityQueue<E,C>::size() const
{ return L.size(); }

template<class E, template<class> class C >
bool ListPriorityQueue<E,C>::empty() const
{ return L.empty(); }

template<class E, template<class> class C >
void ListPriorityQueue<E,C>::insert(const E& e)
{
    typename list<E>::iterator p;
    p = L.begin();

    while(p!=L.end() && !isLess(e, *p))
        ++p;

    L.insert(p, e);
}

template<class E, template<class> class C >
const E& ListPriorityQueue<E,C>::min() const
{
    return L.front();
}

template<class E, template<class> class C >
void ListPriorityQueue<E,C>::removeMin()
{
    L.pop_front();
}

template<class E, template<class> class C >
void ListPriorityQueue<E,C>::print()
{
    typename list<E&>::iterator p;
    for(p = L.begin(); p != L.end(); ++p)
        cout<<" "<< *p;
         cout<<" ";

   
}

template<class E, template<class> class C >
list<E> PriorityQueueSort(list<E> L, ListPriorityQueue<E, C> P)
{

    while(!L.empty())
    {
        E& e = L.front();
        L.pop_front();
        P.insert(e);
    }

    while(!P.empty())
    {
        E e = P.min();
        P.removeMin();
        L.push_back(e);
    }

    return L;
}

int main()
{
    
    return 0;
}
