//Хип, реализиране на приоритетна опашка чрез хип
//◦ add(e) – Добавя към T и връща нов външен възел v съхраняващ елемента e, така че полученото дърво е пълно двоично дърво с последен възел v.
//◦ remove() – Премахва последния възел на T и връща неговият елемент.
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template <typename E>
class VectorCompleteTree {
    private:
        vector<E> V; // Tree contents
    public:
        typedef typename vector<E>::iterator Position;
    protected:
        Position pos(int i) // Index to position
        { return V.begin() + i; }
        int idx(const Position& p) const // Position to index
        { return p - V.begin(); }
    public:
        VectorCompleteTree() : V(1) {} // Constructor
        int size() const                       { return V.size() - 1; }
        Position left(const Position& p)       { return pos(2*idx(p)); }
        Position right(const Position& p)      { return pos(2*idx(p) + 1); }
        Position parent(const Position& p)     { return pos(idx(p)/2); }
        bool hasLeft(const Position& p) const  { return 2*idx(p) <= size(); }
        bool hasRight(const Position& p) const { return 2*idx(p) + 1 <= size(); }
        bool isRoot(const Position& p) const   { return idx(p) == 1; }
        Position root()                        { return pos(1); }
        Position last()                        { return pos(size()); }
        void addLast(const E& e)               { V.push_back(e); }
        void removeLast()                      { V.pop_back(); }
        void swap(const Position& p, const Position& q)
        { E e = *q; *q = *p; *p = e; }
};

// Comparator
template <class T>
class LexCompare {
public:
    // Lex comparison
    int operator()(const T& p1, const T& p2) const
    {
        return p1 < p2;
    }
};

template <class E, template<class> class C>
class HeapPriorityQueue {
    public:
        int size() const;
        bool empty() const;
        void insert(const E& e); // Insert element
        const E& min(); // Get minimum element
        void removeMin(); // Remove minimum element
        void print(); // Print Queue
    private:
        // Shortcut for tree position
        typedef typename VectorCompleteTree<E>::Position Position;
        void show(Position p, int loc); // Show the values in the heap
    private:
        VectorCompleteTree<E> T; // Priority queue contents
        C<E> isLess; // Less-than comparator
};

template <class E, template<class> class C>
int HeapPriorityQueue<E,C>::size() const
{ return T.size(); }

template <class E, template<class> class C>
bool HeapPriorityQueue<E,C>::empty() const
{ return size() == 0; }

// Get minimum element
template <class E, template<class> class C>
const E& HeapPriorityQueue<E,C>::min()
{ return *(T.root()); }

// Insert new element
template <class E, template<class> class C>
void HeapPriorityQueue<E,C>::insert(const E& e) {
    T.addLast(e); // Add element e to the heap

    Position v = T.last(); // Get e�s position

    // Up-heap bubbling
    while (!T.isRoot(v)) {
        Position u = T.parent(v);
        if (!isLess(*v, *u))
            break; // if v in order

        T.swap(v, u); // Swap with parent

        v = u;
    }
}

// Remove minimum
template <class E, template<class> class C>
void HeapPriorityQueue<E,C>::removeMin() {
    if (size() == 1)
        T.removeLast();
    else
    {
        Position u = T.root(); // Root position

        T.swap(u, T.last()); // Swap last with root
        T.removeLast(); // Remove last

        while (T.hasLeft(u))
        {
            // Down-heap bubbling
            Position v = T.left(u);
            if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                v = T.right(u); // v is u�s smaller child

            // Is u out of order?
            if (isLess(*v, *u))
            {
                T.swap(u, v); // Swap
                u = v;
            }
            else
                break;
        }
    }
}

// Print Queue
template <class E, template<class> class C>
void HeapPriorityQueue<E,C>::print()
{
    int loc = 8; // To format the output

    Position p = T.root(); // Root position
    cout<<"Root: "<< *p <<endl; // Show root

    Position leftChild = T.left(p); //Get root left child
    show(leftChild, loc); // Travers the left subtree
    cout<<"\n";

    Position rightChild = T.right(p); //Get root right child
    show(rightChild, loc); // Travers the right subtree
}

 // Show the values in the heap
template <class E, template<class> class C>
void HeapPriorityQueue<E,C>::show(Position p, int loc)
{
    loc += 2;
    cout<<setw(loc)<<*p<<endl;

    //Check for left child
    if(T.hasLeft(p))
    {
        Position leftChild = T.left(p); //Get left child
        show(leftChild, loc); //Recursive traversal of left subtree
        cout<<"\n";
    }

    //Check for right child
    if(T.hasRight(p))
    {
        Position rightChild = T.right(p); //Get right child
        show(rightChild, loc); //Recursive traversal of right subtree
    }
}

int main()
{
    HeapPriorityQueue<int, LexCompare> hPQ1;

    for(int i = 0; i<9;i++)
        hPQ1.insert(i);

    hPQ1.print();

    hPQ1.removeMin();

    hPQ1.print();
    return 0;
}
