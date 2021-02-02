
// Задача 1. Реализирайте алгоритъма за сортиране с приоритетна опашка, който е описан по-горе.
// Задача 2. Реализирайте приоритетна опашка, с помощта на която да намерите медианата на редица от числа.
//◦ Дефиниция. Медиана на редица от n числа [a1, a2, ..., an] e средата на сортираната редица:
// Когато n е нечетно число, медианата е средният елемент на позиция n / 2 в сортираната редица от числа.
// Когато n е четно число, медианата е средно-аритметичното на двата средни елемента в сортираната редица от числа.
// Задача 3. Напишете програма, която позволява на потребителя да въведе редица А от n числа, цяло число k и цяло число l. Програмата трябва да изведе k-ти най-малък елемент l-ти най- голям елемент в А, сумата и средноаритметичната стойност на k-тия най-малък и l-тия най-голям,.
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
    ListPriorityQueue<int, LexCompare> pQ1;
    pQ1.insert(2);
    pQ1.insert(10);
    pQ1.insert(5);
    pQ1.insert(3);
    pQ1.insert(1);

    cout<<"pQ1: ";
    pQ1.print();
    cout<<endl;

    //Lab exercise 1
    list<int> l1;
    typename list<int>:: iterator p;
    p = l1.begin();

    srand(time(0));
    for(int i = 0; i< 10; i++)
    {
        l1.insert(p, rand()%101);
        ++p;
    }

    cout<<"List before sort: " ;
    for(p = l1.begin(); p != l1.end();++p)
    { cout<<setw(5)<<*p; }
     cout<<" ";
    

    ListPriorityQueue<int, LexCompare> pQ2;
    l1 = PriorityQueueSort(l1, pQ2);

    cout<<"List after sort: " ;
    for(p = l1.begin(); p != l1.end();++p)
    { cout<<setw(5)<<*p; }
    cout<<" ";

    //Lab exercise 2

    int tmp = 0, tmp2 = 0, n;
    cout<<"n= " ;
    cin>>n;
    ListPriorityQueue<int, LexCompare> pQ3;
    for(int i = 0; i< n; i++)
        pQ3.insert(rand()%101);

    pQ3.print();

    if(pQ3.size() % 2 != 0)
    {
        for(int i = 0; i <= pQ3.size() / 2; i++)
            pQ3.removeMin();

        tmp = pQ3.min();
        cout<<"Med: "<<((double)tmp/2)<<endl;
    }
    else
    {
        for(int i = 0; i <= pQ3.size() / 2; i++)
            pQ3.removeMin();

        tmp = pQ3.min();
        pQ3.removeMin();
        tmp2 = pQ3.min();
        cout<<"Med: " <<(double)(tmp+tmp2)/2<<endl;
    }

    //Lab exercise 3
    int k, l;
    cout<<"k = " ;
    cin>>k;
     cout<<"l = ";
    cin>>l;
    p = l1.begin();
    for(int i = 0; i < k-1; i++)
        ++p;
    k = *p;

    p = l1.end();
    for(int i = 0; i < l; i++)
        --p;
    l = *p;

cout<<"k =  "<<k<<"l= "<<l<<endl;
    return 0;
}