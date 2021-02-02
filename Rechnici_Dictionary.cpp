#include <iostream>
#include <list>
#include <iomanip>

using namespace std;

template<typename K, typename V>
class ListDictionary
{
    public:
        class Pair
        {
            private:
                K _key;
                V _value;
            public:
                Pair(const K& k = K(), const V& v = V()) : _key(k), _value(v) { }

                const K& getKey() const { return _key; }
                void setKey(const K& k) { _key = k; }

                const V& getValue() const { return _value; }
                void setValue(const V& v) { _value = v; }
        };

        typedef typename list<Pair>::iterator MIter;
        ListDictionary() : n(0) { }
        int size() const   { return n; }
        bool empty() const { return size() == 0; }
        MIter begin()      { return LDict.begin(); }
        MIter end()        { return LDict.end(); }
        MIter find(const K& k);
        MIter* findAll(const K& k, MIter* arr);
        MIter insert(const K& k, const V& v);
        void erase(const K& k);
        void erase(const MIter& p);
        void eraseAll(const K& k);
        void print();
    private:
        list<Pair> LDict;
        int n;
};

template<typename K, typename V>
typename ListDictionary<K,V>::MIter ListDictionary<K,V>::find(const K& k)
{
    for(MIter p = LDict.begin(); p != LDict.end(); p++)
    {
        Pair currentPair = *p;
        if(currentPair.getKey() == k)
            return p;
    }
    return end();

}

template<typename K, typename V>
typename ListDictionary<K,V>::MIter* ListDictionary<K,V>::findAll(const K& k, MIter* arr)
{
   ListDictionary<K,V>::MIter b = LDict.begin();
   ListDictionary<K,V>::MIter e = LDict.end();
   ListDictionary<K,V>::MIter tmp;

   for(MIter p = LDict.begin(); p != LDict.end(); p++)
   {
       Pair currentPair = *p;
       if(currentPair.getKey() == k)
       {
            if(b == LDict.begin())
                b = p;
            else
            {

                tmp = p;
                tmp++;
                currentPair = *tmp;
                if(currentPair.getKey() != k)
                {
                    e = tmp;
                }

            }
       }
   }

   arr[0] = b;
   arr[1] = e;
   return arr;
}

template<typename K, typename V>
typename ListDictionary<K,V>::MIter ListDictionary<K,V>::insert(const K& k, const V& v)
{
    Pair newPair;
    newPair.setKey(k);
    newPair.setValue(v);

    MIter p = LDict.begin();
    while(p != LDict.end())
    {
        Pair currentPair = *p;
        if(currentPair.getKey() == k)
        {
            LDict.insert(p, newPair);
            n++;
            return p;
        }
        p++;
    }

    LDict.insert(p, newPair);
    n++;
    return p;
}
template<typename K, typename V>
void ListDictionary<K,V>::erase(const K& k)
{
   for(MIter p = LDict.begin(); p != LDict.end(); p++)
   {
       Pair currentPair = *p;
       if(currentPair.getKey() == k)
       {
           erase(p);
           n--;
           return;
       }
   }
}
template<typename K, typename V>
void ListDictionary<K,V>::erase(const MIter& p)
{
    LDict.erase(p);
    n--;
}

template<typename K, typename V>
void ListDictionary<K,V>::eraseAll(const K& k)
{
    MIter arr[2];
    findAll(k, arr);

    MIter startP = arr[0];
    MIter endP = arr[1];

    Pair sPair = *startP;

    while(sPair.getKey() != (*endP).getKey())
    {
        startP++;
        erase(sPair.getKey());
        sPair = *startP;
    }
}

template<typename K, typename V>
void ListDictionary<K,V>::print()
{
    ListDictionary<K,V>::Pair cPair;
    cout<<setw(6)<<"Keys"<<setw(11)<<"Values"<<endl;
    for(MIter p = LDict.begin(); p != LDict.end(); p++)
    {
        cPair = *p;
        cout<<"Key: "<<cPair.getKey()<<setw(10)<<"Value: "<<cPair.getValue()<<endl;
    }
    cout<<'\n';
}

int main()
{
    ListDictionary<int, int> lDict;
    for(int i = 1; i < 10; i++)
        lDict.insert(i*10, i);

    lDict.insert(50, 51);
    lDict.insert(50, 52);
    lDict.insert(50, 53);
    lDict.print();

    cout<<"Find all elements with key 50"<<endl;
    typename ListDictionary<int, int>::MIter arr[2];
    lDict.findAll(50, arr);
    typename ListDictionary<int, int>::MIter startP = arr[0];
    typename ListDictionary<int, int>::MIter endP = arr[1];

    ListDictionary<int, int>::Pair sPair = *startP;
    ListDictionary<int, int>::Pair ePair = *endP;

    while(sPair.getKey() != ePair.getKey())
    {
        cout<<sPair.getKey()<<" "<<sPair.getValue()<<endl;
        startP++;
        sPair = *startP;
    }
    cout<<endl;

    cout<<"Find element with specific key"<<endl;
    typename ListDictionary<int, int>::MIter f = lDict.find(60);
    ListDictionary<int, int>::Pair fPair = *f;
    cout<<fPair.getKey()<<" "<<fPair.getValue()<<endl;

    cout<<"\nRemove all elements with key 50"<<endl;
    lDict.eraseAll(50);
    lDict.print();
    return 0;
}
