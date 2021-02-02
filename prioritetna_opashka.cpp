#include <iostream>
#include <iomanip>
#include <list>
#include <stdlib.h>
#include <time.h>
using namespace std;
template <class T>
 class LexCompare{
public: 
    int operator()(const T& a,const T& b) const{
    return a<b;
}
 };
 template<class E, template<class>class C>
 class ListPriorityQueue{
public:
int size() const;
bool empty() const;
void insert(const E& e);
E& min() const;
void removeMin();
void print();
private:
list<E>L;
C<E>isLess;

 };
 template<class E, template<class>class C>
 int  ListPriorityQueue<E,C>::size() const{
     return L.size();
 }
  template<class E, template<class>class C>
 bool  ListPriorityQueue<E,C>::empty() const{
return L.empty();
 }
  template<class E, template<class>class C>
 void  ListPriorityQueue<E,C>::insert(const E& e) {
     typename list<E> :: iterator p;
     p=L.begin();
     while (p!=L.end() && !isLess(e, *p))
     
         ++p;
         L.insert(p,e);
     
     
 }
 template<class E, template<class>class C>
  E& ListPriorityQueue<E,C>::min() const{
     return L.front();
 }
template<class E, template<class>class C>
 void  ListPriorityQueue<E,C>::removeMin(){
     L.pop_front;
 } 
 template<class E, template<class>class C>
 void  ListPriorityQueue<E,C>::print(){
     typename list<E>::iterator p;
     for(p=L.begin(); p!=L.end();++p)
     cout<<'\t'<<*p;;
     cout<<endl;
 }

 int main(){
     ListPriorityQueue<int, LexCompare>queue1;
     queue1.insert(10);
      queue1.insert(2);
       queue1.insert(102);
        queue1.insert(46);
         queue1.insert(1);
         cout<<"Rezult: ";
         queue1.print();
         cout<<endl;
     return 0;
 }