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
template <typename T>
class L
{
    private:
       struct Node
       {
           T elem;
           Node* next;
           Node* prev;          
       };
    public:
       class Iterator
       {
           public:
              Node* v;
              Iterator (Node* u)
              { v = u; }
           public:
              T& operator* () { return v->elem; }

              bool operator==(const Iterator& p) const
              { return v == p.v; }

              bool operator!=(const Iterator& p) const
              { return v != p.v; }

              Iterator& operator++()
              {
                 v = v->next;
                 return *this; 
              }

              Iterator& operator--()
              {
                 v = v->prev;
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

            int size() const { return n; }
            bool empty() const { return (n == 0);}
            Iterator begin() const {return Iterator(header->next); }
            Iterator end() const { return Iterator(trailer); }

            void insertFront(const T& e) { insert(begin(), e); }
            void insertBack(const T& e) { insert(end(), e); }
            void insert(const Iterator& p, const T& e);

            void eraseFront() { erase(begin()); }
            void eraseBack() { erase(--end());}
            void erase(const Iterator& p);

            void print();
};

template <typename T>
L <T>::L()
{
   n = 0;

   header = new Node;
   trailer = new Node;

   header->next = trailer;
   trailer->prev = header;
}

template <typename T>
L <T>::L(const L <T>& n1)
{
   n = n1.size();

   header = new Node;
   trailer = new Node;

   header->next = trailer;
   trailer->prev = header;

   Iterator itTemp = Iterator(n1.begin());
   int index = 0;
   while(index < n1.size())
   {
      Node* nd = itTemp.v;
      insertBack(nd->elem);
      ++itTemp;
      index++;
   }
}
template <typename T>
L <T>::~L()
{
   int index = 0;
   Iterator itTemp = Iterator(begin());
   while(index < size())
   {
      Node* nd = itTemp.v;
      delete &nd;
      index++;
      ++itTemp;
   }

   delete &n;
   delete &header;
   delete &trailer;
}
template <typename T>
L<T>& L<T> ::operator=(const L<T>& n1)
{
   if(this != &n1)
   {
      n = n1.size();

      Iterator itTemp = Iterator(n1.begin());
      --itTemp;
      header = itTemp.v;

      itTemp = Iterator(n1.end());
      trailer = itTemp.v;
   }

   return *this;
}

template <typename T>
void L<T>::insert(const L<T>::Iterator& p, const T& e)
{
   Node* w = p.v;
   Node* u = w->prev;

   Node* v = new Node;
   v->elem = e;
   v->next = w; w->prev = v;
   v->prev = u; u->next = v;
   n++;
}

template<typename T>
void L<T>::erase(const L<T>::Iterator& p)
{
    Node* v = p.v;
    Node* w = v->next;
    Node* u = v->prev;

    u->next = w; w->prev = u;
    delete v;
    n--;
}

template<typename T>
void L<T>::print()
{
    int index = 0;
    Iterator item = begin();

    while(index < size())
    {
        Node* nd = item.v;
        cout << nd->elem << " ";
        ++item;
        index++;
    }
    cout << endl;
}
int main()
{
    int N, tmp;
    int b = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0;
    int b5 = 0, b6 = 0, b7 = 0, b8 = 0, b9 = 0;

    L<int>*  list1 = new L<int>();
    L<int>*  list2 = new L<int>();
    L<int>::Iterator it = list1->end();

    time_t t;

    srand(time(& t));
    cout << " N = ";
    cin >> N;

    for(int i = 0; i < N; i++)
    {
        tmp = rand() % 9 + 1;
        list1->insertFront(tmp);
    }
    list1->print();

    --it;
    for(int i = 1; i <= list1->size(); i++)
    {
        tmp = *it;
        switch(tmp)
        {
            case 0:
                b++;
                break;
            case 1:
                b1++;
                break;
            case 2:
                b2++;
                break;
            case 3:
                b3++;
                break;
            case 4:
                b4++;
                break;
            case 5:
                b5++;
                break;
            case 6:
                b6++;
                break;
            case 7:
                b7++;
                break;
            case 8:
                b8++;
                break;
            default:
                b9++;
                break;
        }

        list2->insertBack(tmp);
        --it;
    }
    list2->print();
    cout<< "9: " << b9 << ", 8: " << b8 << ", 7: " << b7 << ", 6: " << b6 << ", 5: " << b5;
    cout<< ", 4: "<< b4 << ", 3: " << b3<< ", 2: " << b2<< ", 1: " << b1<< ", 0: " << b <<endl;


    return 0;
}