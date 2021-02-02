#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;
template<class T>
class LexCompare
{
    public:
        int operator()(const T& a, const T& b) const
        { return a < b; }
};

template <class E, template<class> class C>
class ListPriorityQueue
{
    public:
        int size() const;
        bool empty() const;
        void insert(const E& e);
        const E& min() const;
        void removeMin();
        void print();
    private:
        list<E> L;
        C<E> isLess;
};
template <class E, template<class> class C>
int ListPriorityQueue<E,C>::size() const
{ return L.size(); }

template <class E, template<class> class C>
bool ListPriorityQueue<E,C>::empty() const
{ return L.empty(); }

template <class E, template<class> class C>
void ListPriorityQueue<E,C>::insert(const E& e)
{
    typename list<E>::iterator p;
    p = L.begin();

    while(p != L.end() && !isLess(e, *p))
        ++p;

    L.insert(p, e);
}

template <class E, template<class> class C>
const E& ListPriorityQueue<E,C>::min() const
{ return L.front(); }

template <class E, template<class> class C>
void ListPriorityQueue<E,C>::removeMin()
{ return L.pop_front(); }

template <class E, template<class> class C>
void ListPriorityQueue<E,C>::print()
{
    typename list<E>::iterator p;
    for(p = L.begin(); p!=L.end(); ++p)
        cout<<'\t'<<*p;

    cout<<endl;
}

template <class E, template<class> class C>
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
    pQ1.print();

    // Lab Exercise 1

    list<int> l1;
    typename list<int>::iterator p;
    p=l1.begin();

    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        l1.insert(p, rand()%101);
        ++p;
    }

    cout<<"The list before sort: ";
    for(p = l1.begin(); p != l1.end(); ++p)
        cout<<setw(5)<<*p;
    cout<<'\n';

    ListPriorityQueue<int, LexCompare> pQ2;
    l1 = PriorityQueueSort(l1, pQ2);

    cout<<"The list after sort: ";
    for(p = l1.begin(); p != l1.end(); ++p)
        cout<<setw(5)<<*p;
    cout<<'\n';
    //2
int n, tmp1, tmp2;
cout<<"n = ";
cin>>n;

ListPriorityQueue<int, LexCompare> pQ3;
for(int i = 0; i < n; i++)
pQ3.insert(rand()%101);

pQ3.print();

if(pQ3.size() % 2 != 0 )
{
for(int i = 0; i <= pQ3.size()/2; i++)
pQ3.removeMin();

cout<<"Med: "<<(double)pQ3.min()/2<<endl;
}
else
{
for(int i = 0; i <= pQ3.size()/2; i++)
pQ3.removeMin();
tmp1 = pQ3.min();
pQ3.removeMin();
tmp2 = pQ3.min();

cout<<tmp1<<" "<<tmp2<<endl;
cout<<"Med: "<<((double)(tmp1+tmp2)/2)<<endl;

}

    return 0;
}