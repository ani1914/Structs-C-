//Структурата от данни Map съхранява двойки ключ-стойност (k, v), наречени записи (entries), където k е ключът, а v е съответната стойност.
//◦ size()–Връща броя на записите в структурата;
//◦ empty() – Връща true, ако структурата е празна и false в противен случай;
//◦ find(k)–Ако структурата съдържа записe=(k,v),сключk,тогаватози метод връща итератор p, отнасящ се до този запис. В противен случай методът връща специалният итератор end;
//◦ insert(k, v) – Ако структурата не съдържа запис с ключ k, то методът добавя записа (k, v) в структурата. В противен случай заменя стойността на запис с ключ k с новата стойност v. Методът връща итератор към вмъкнатия / модифицирания запис;
//◦ erase(k) – Премахва запис с ключ, равен на k;
//◦ erase(р) – Премахва записа, посочен от итератора р;
//◦ begin()–Връщаитераторкъмпървиязаписвструктурата;
//◦ end()–Връща итератор към позициятаточноследкраянаструктурата.
#include <iostream>
#include <list>
#include <iomanip>
using namespace std;


template <typename K, typename V>
class ListMap {
    public:
        //(key, value) pair
        class Pair {
            public:
                Pair(const K& k = K(), const V& v = V()) : _key(k), _value(v) { }
                const K& getKey() const   { return _key; }     // Get key
                void setKey(const K& k)   { _key = k; }        // Set key
                const V& getValue() const { return _value; }   // Get value
                void setValue(const V& v) { _value = v; }      // Set value
            private:
                K _key;                     // Key
                V _value;                   // Value
        };

        typedef typename list<Pair>::iterator MIter;
        ListMap() : n(0) {}
        int size() const   { return n; }           // Number of entries
        bool empty() const { return size() == 0; } // Is the map empty?
        MIter begin()      { LMap.begin(); }       // Iterator to first entry
        MIter end()        { LMap.end(); }         // Iterator to end entry
        MIter find(const K& k) const;              // Find entry with key k
        MIter put(const K& k, const V& v);         // Insert/replace pair (k,v)
        void erase(const K& k);                    // Remove entry with key k
        void erase(const MIter& p);                // Remove entry on position p
        void print();
    private:
        int n;                              // Number of entries
        list<Pair> LMap;
};

// Find entry with key k
template <typename K, typename V>
typename ListMap<K,V>::MIter ListMap<K,V>::find(const K& k) const
{
    for (MIter p=LMap.begin(); p!=LMap.end(); p++)
    {
        if (p.getKey() = k)
            return p;
    }
    return end();
}

// Insert/replace pair (k,v)
template <typename K, typename V>
typename ListMap<K,V>::MIter ListMap<K,V>::put(const K& k, const V& v)
{
    Pair newPair = Pair(k,v);
    MIter p = LMap.begin();
    while (p!=LMap.end())
    {
        Pair currentPair = *p;
        if (currentPair.getKey() == k)
        {
            *p = newPair;
            return p;
        }
        p++;
    }
    LMap.insert(p, newPair);
    n++;
    return p;
}

// Remove entry with key k
template <typename K, typename V>
void ListMap<K,V>::erase(const K& k)
{
    for (MIter p=LMap.begin(); p!=LMap.end(); p++)
    {
        if (p.getKey() = k)
        {
            LMap.erase(p);
            n--;
        }
    }
}

// Remove entry on position p
template <typename K, typename V>
void ListMap<K,V>::erase(const MIter& p)
{
    LMap.erase(p);
    n--;
}

template <typename K, typename V>
void ListMap<K,V>::print()
{
    ListMap<int, int>::Pair cPair;
    cout<<setw(6)<<"Keys"<<setw(11)<<"Values"<<endl;
    for (MIter p=LMap.begin(); p!=LMap.end(); p++)
    {
        cPair = *p;
        cout<<"Key: "<<cPair.getKey()<<setw(10)<<"Value: "<<cPair.getValue()<<endl;
    }
}
int main()
{
    ListMap<int, int> LMap1;

    for(int i = 1; i<=9;i++)
        LMap1.put(i*10, i);

    LMap1.print();

    return 0;
}
