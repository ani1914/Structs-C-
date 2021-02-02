//Задача 1. Реализирайте структура от данни Map с хеш таблица, с помощта на която да решите следните задачи:
//а). Напишете програма, която премахва всички числа, които се срещат нечетен брой пъти в дадена редица. Например, ако имаме началната редица {4, 2, 2, 5, 2, 3, 2, 3, 1, 5, 2, 6, 6, 6},трябва да я редуцираме до редицата {5, 3, 3, 5}.
//б). Напишете програма, която брои колко пъти се среща всяко число в дадена редица от числа.
//Пример: array = {3, 4, 4, 2, 3, 3, 4, 3, 2} 2 -> 2 пъти
//3 -> 4 пъти
//4 -> 3 пъти
#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
using namespace std;

//(key, value) pair
template <typename K, typename V>
class Pair {
    public:
        Pair(const K& k = K(), const V& v = V()) : _key(k), _value(v) { }
        const K& getKey() const   { return _key; }     // Get key
        void setKey(const K& k)   { _key = k; }        // Set key
        const V& getValue() const { return _value; }   // Get value
        void setValue(const V& v) { _value = v; }      // Set value
    private:
        K _key;                     // Key
        V _value;                   // Valuee
};

// Comparator
class HComp {
public:
    int operator()(const int& i) const
    { return i; }
};

template <typename K, typename V, typename H>
class HashMap {
    public:
        typedef Pair<const K,V> Entry; //(key,value) pair
        class Iterator;                // Iterator
    public:
        // Constructor
        HashMap(int capacity = 100) : n(0), B(capacity) { }
        int size() const { return n; }             // Number of entries
        bool empty() const { return size() == 0; } // Is the map empty?
        Iterator find(const K& k);                 // Find key
        Iterator put(const K& k, const V& v);      // Insert/replace (k,v)
        void erase(const Iterator& p) {eraser(p);} // Remove entry at position p
        void erase(const K& k);                    // Remove entry with key k
        Iterator begin();                          // Iterator to first entry
        Iterator end();                            // Iterator to end entry
        void print();
    protected:
        typedef list<Entry> Bucket;                // Bucket of entries
        typedef vector<Bucket> BktArray;           // Bucket array
        typedef typename Bucket::iterator EItor;   // Entry iterator
        typedef typename BktArray::iterator BItor; // Bucket iterator
        void nextEntry(Iterator& p) { ++p.ent; }   // Bucket�s next entry
        bool endOfBkt(const Iterator& p)           // End of bucket
        { return p.ent == p.bkt->end(); }
        Iterator finder(const K& k);               // Find utility
        Iterator inserter(const Iterator& p, const Entry& e); // Insert utility
        void eraser(const Iterator& p);            // Remove utility
    private:
        int n;       // Number of entries
        H hash;      // The hash comparator
        BktArray B;  // Bucket array
    public:
        class Iterator {
            private:
                EItor ent;                // Which entry
                BItor bkt;                // Which bucket
                const BktArray* ba;       // Which bucket array
            public:
                Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
                : ent(q), bkt(b), ba(&a) { }
                Entry& operator*() const;                 // Get entry
                bool operator==(const Iterator& p) const; // Are the iterators equal?
                Iterator& operator++();                   // Next entry
                friend class HashMap;                     // Give HashMap access
        };
};

// Get entry
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Entry& HashMap<K,V,H>::Iterator::operator*() const
{ return *ent; }

// Are the iterators equal?
template <typename K, typename V, typename H>
bool HashMap<K,V,H>::Iterator::operator==(const Iterator& p) const {
    if (ba != p.ba || bkt != p.bkt)
        return false; // ba or bkt differ?
    else if (bkt == ba->end())
        return true; // both at the end?
    else
        return (ent == p.ent); // else use entry to decide
}

// Next entry
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator& HashMap<K,V,H>::Iterator::operator++() {
    ++ent; // Next entry in bucket
    // At end of bucket
    if (endOfBkt(*this)) {
        ++bkt; // Go to next bucket

        // Try to find nonempty bucket
        while (bkt != ba->end() && bkt->empty())
            ++bkt;

        // Check for end of bucket array
        if (bkt == ba->end())
            return *this;

        ent = bkt->begin(); // First nonempty entry
    }
    return *this; // Return self
}

// Find key
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::find(const K& k)
{
    Iterator p = finder(k); // Try to find k
    if (endOfBkt(p))
        return end(); // Return end iterator
    else
        return p; // Return its position
}

// Find utility
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::finder(const K& k)
{
    int i = hash(k) % B.size(); // Get hash index i
    BItor bkt = B.begin() + i; // The i-th bucket
    Iterator p(B, bkt, bkt->begin()); // Start of i-th bucket
    while (!endOfBkt(p) && (*p).getKey() != k) // Search for k
        nextEntry(p);
    return p; // Return final position
}

// Insert/Replace (k,v)
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::put(const K& k, const V& v)
{
    Iterator p = finder(k); // Try to find k
    if (endOfBkt(p)) // k is not found?
        return inserter(p, Entry(k, v)); // Insert at end of bucket
    else
    {
        p.ent->setValue(v); // Replace value with v
        return p; // Return this position
    }
}
// Insert utility
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::inserter(const Iterator& p, const Entry& e)
{
    EItor ins = p.bkt->insert(p.ent, e); // Insert before p
    n++;
    return Iterator(B, p.bkt, ins); // Return this position
}

// Remove entry with key k
template <typename K, typename V, typename H>
void HashMap<K,V,H>::erase(const K& k)
{
    Iterator p = finder(k); // Try to find k
    if (endOfBkt(p))  // k is not found?
    {
        cout<<"Erase of nonexistent"; // . . .error
        return;
    }
    eraser(p); // Remove it
}

// Remove utility
template <typename K, typename V, typename H>
void HashMap<K,V,H>::eraser(const Iterator& p)
{
    p.bkt->erase(p.ent); // Remove entry from bucket
    n--;
}

// Iterator to end entry
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::end()
{ return Iterator(B, B.end()); }

// Iterator to first entry
template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::begin()
{
    if (empty())
        return end();
    BItor bkt = B.begin();                 // Search for an entry
    while (bkt->empty())                   // Try to find nonempty bucket
        ++bkt;
    return Iterator(B, bkt, bkt->begin()); // Return first of bucket
}

template <typename K, typename V, typename H>
void HashMap<K,V,H>::print()
{
    cout<<setw(5)<<"Keys"<<setw(13)<<"Values"<<endl;
    for(int i = 1; i<=size(); i++)
    {
        BItor bkt = B.begin() + i;
        Iterator p(B, bkt, bkt->begin());
        while (!endOfBkt(p))
        {
            int out = 12;
            if(i>9)
                out = 11;
            cout<<"Key: "<<(*p).getKey()<<setw(out)<<"Value: "<<(*p).getValue()<<endl;
            nextEntry(p);
        }
    }
}

int main()
{
    HashMap<int, char, HComp> hMap = HashMap<int, char, HComp>(200);
    char c = 'a';

    for(int i = 1; i<=26;i++)
    {
        int key = i;
        hMap.put(key, c);
        c = c + 1;
    }

    hMap.print();

    return 0;
}
