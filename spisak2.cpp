/*
begin() – Връща итератор, отнасящ се до първия елемент на L (5%);
 end() – Връща итератор, отнасящ се до контролен елемент непосредствено след
последния елемент на L (5%);
 size() – връща броя на елементите в свързаният списък (5%);
 isEmpty() – връща булева стойност, показваща дали списъкът е празен (5%);
 insertFront(e) – Вмъква нов елемент (стойност) e в L като първи елемент (5%);
 insertBack(e) – Вмъква нов елемент (стойност) e в L като последен елемент (5%);
 insert(p, e) – Вмъква нов елемент (стойност) e в L преди позиция p (10%);
 eraseFront() – Премахва първия елемент на L (5%);
 eraseBack() – Премахва последния елемент от L (5%);
 erase(p) – Премахва от L елемента на позиция p (10%).
 at(i) – Връща елемента (стойността) на позиция i (5%);
 set(i, e) – Заменя елемента (стойността) на позиция i с e (5%).
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

template<typename T>
class L
{
private:
   struct Node
   {
       T elem;
       Node* prev;
       Node* next;
   };
   
public:
class Iterator
{

public:
Node* v;
    Iterator( Node* u){
        v=u;
    }
    public: 
   T& operator*(){
       return v-> elem;
   }
   bool operator ==(const Iterator& p) const{
       return (v==p.v);
   }
    bool operator !=(const Iterator& p) const{
       return (v!=p.v);
   }
   Iterator& operator++(){
       v=v->next;
       return *this;
   }
   Iterator& operator--(){
       v=v->prev;
       return *this;
   }

};
private:
int n;
Node* header;
Node* trailer;

public:
L();
L(const L& nl);
~L();
L& operator=(const L& nl);
 
 int size() const{
     return n;}
 bool isEmpty()const{
     return (n==0);
 }
 Iterator begin() const{
    return Iterator(header->next);
 }
 Iterator end() const{
     return Iterator(trailer);
 }
 void insertFront(const T& e){
     insert(begin(), e);
 }
 void insertBack(const T& e){
     insert(end(), e);
 }
 void insert(const Iterator& p, const T& e){
Node* w=p.v;
Node* u=w->prev;
Node* v=new Node;
v->elem=e;
v->next=w;
w->prev=v;
v->prev=u;
u->next=v;
n++;
 }


 
 void eraseFront(){
     erase(begin());
 }
 void eraseBack(){
     erase(--end());
 }
  void erase(const Iterator& p){
     Node* v=p.v;
     Node* w=v->next;
     Node* u=v->prev;

     u->next=w;
     w->prev=u;
     
     delete v;
     n--;
 }
 void print();


   
};
template<typename T>
L<T>::L(){

    n=0;

    header=new Node;
    trailer=new Node;
     
    header->next=trailer;
    trailer->prev=header;
}

template<typename T>
L<T>::L(const L& nl){
    n=nl.size(); 

    
  
    header=new Node;
    trailer=new Node;

    header->next=trailer;
    trailer->prev=header;

    Iterator itTemp=Iterator(nl.begin());
    int index=0;
    while (index<nl.size())
    {
        Node* nd=itTemp.v;
        insertBack(nd->elem);
        ++itTemp;
        index++;
    }
    
}

template<typename T>
L<T>::~L(){
    int index=0;
    Iterator itTemp=Iterator(begin());
    while (index<size())
    {
       Node* nd=itTemp.v;
       delete &nd;
       index++;
       ++itTemp;
    }
       delete &n;
       delete &header;
       delete &trailer;
    
    
    
}

template<typename T>
L<T>& L<T>::operator=(const L<T>& nl){
    if(this!=&nl){
        n=nl.size();
        Iterator itTemp=Iterator(nl.begin());
        --itTemp;
        header=itTemp.v;
          itTemp=Iterator(nl.end());
       
        trailer=itTemp.v;
    }
    return *this;
}
template<typename T>
void L<T>::print(){
    int index=0;
    Iterator item=begin();
    while(index<size()){
        Node* nd=item.v;
        cout<<nd->elem<<" ";
        ++item;
        index++;
    }
}



int main(){
    L<int>* list1=new L<int>();
    list1->insertFront(1);
    list1->insertFront(2);
    list1->insertFront(3);
    list1->insertFront(5);

    cout<<"This list size: "<<list1->size()<<endl;
    list1->print();
   
    return 0;
}
