//Задача 1. Даден е файла zipcodes.txt, който съдържа пощенски кодове на градове. Напишете програма, която прочита 
//файла zipcodes.txt и съхранява пощенските кодове във вектор. След това програмата трябва да обходи вектора и да създаде Map, където пощенските кодове са ключове, а броя 
//на срещанията на даде ключ във файла zipcodes.txt е стойността, т.е. за двойката (ключ, стойност), ключ – пощенски код, стойност – брой повторения на пощенския код (ключа) във файла zipcodes.txt.
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
    int arr[] = {4, 2, 2, 5, 2, 3, 3, 1, 5, 2, 6, 6, 6};
    int br = 0;
    for(int i = 0; i < 12; i++)
    {
        br = 0;
        for(int j = i; j < 13; j++)
        {
            if(arr[i] == arr[j])
                br++;
        }

        if(lDict.empty())
            lDict.insert(arr[i], br);
        else
        {
            if(lDict.find(arr[i])==lDict.end())
                lDict.insert(arr[i], br);
        }
    }
    lDict.print();

    ListDictionary<int, int>::MIter p = lDict.begin();
    ListDictionary<int, int>::Pair cPair = *p;

    while(true)
    {
        if(p == lDict.end())
        {
            if(cPair.getValue() % 2 != 0)
                lDict.erase(cPair.getKey());
            break;
        }

        p++;

        if(cPair.getValue() % 2 != 0)
            lDict.erase(cPair.getKey());

        cPair = *p;
    }
    /*
    for(p = lDict.begin(); p != lDict.end(); p++)
    {
        ListDictionary<int, int>::MIter tmp = p;

        ListDictionary<int, int>::Pair cPair = *tmp;

        if(cPair.getValue() % 2 != 0)
            lDict.erase(tmp);


    }
*/
    lDict.print();
    return 0;
}
