//Задача 1. Реализирайте двоично дърво, където всеки възел съхранява някаква целочислена стойност. Напишете програма която извежда, най-малката, най-голямата и сумата от всички стойности в дървото.
//Задача 2. Реализирайте методи, който намират дълбочината и височината на дърво.
//Освен това, позиция p поддържа следните операции:
//◦ p.left() – връща лявото дете на възела на позиция p;
//◦ p.right() – връща дясното дете на възела на позиция p;
//◦ p.parent() – връща родителя на възела на позиция p;
//◦ p.isRoot() – връща true, ако възела на позиция p е корен и false, в противен случай;
//◦ p.isExternal() – връща true, ако възела на позиция p е външен и false, в противен случай.
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

typedef int Elem;
class BinaryTree
{
    protected:
        struct Node
        {
            Elem elt;
            Node* par;
            Node* left;
            Node* right;
            Node(): elt(), par(NULL), left(NULL), right(NULL) {}
        };
    public:
        class Position
        {
            private:
                Node* v;
                Position(Node* v = NULL) : v(v) {}
            public:
                Elem& operator*()
                { return v->elt; }

                Position left() const
                { return (Position(v->left)); }

                Position right() const
                { return (Position(v->right)); }

                Position parent() const
                { return (Position(v->par)); }

                bool isRoot() const
                { return v->par == NULL; }

                bool isExternal() const
                { return (v->left == NULL && v->right == NULL); }

                friend class BinaryTree;
        };
        typedef vector<Position> PositionList;
    public:
        BinaryTree();
        int size() const;
        bool empty() const;
        Position root() const;
        PositionList positions() const;
        void addRoot();
        void expendExternal(const Position& p);
        Position removeAboveExternal(const Position& p);

        void print(PositionList pl);
        void preorderPrint(const BinaryTree* T, Position& p);
        int depth(const BinaryTree* T, const Position& p ); // Lab exercise 2
    protected:
        void preorder(Node* v, PositionList& pl) const;
    private:
        Node* _root;
        int n;
};

BinaryTree::BinaryTree() : _root(NULL), n(0)
{}

int BinaryTree::size() const
{ return n; }

bool BinaryTree::empty() const
{return size() == 0; }

BinaryTree::Position BinaryTree::root() const
{ return Position(_root); }

void BinaryTree::addRoot()
{
    _root = new Node;
    n = 1;
}

void BinaryTree::expendExternal(const Position& p)
{
    Node* v = p.v;

    v->left = new Node;
    v->left->par = v;

    v->right = new Node;
    v->right->par = v;

    n += 2;
}

BinaryTree::Position BinaryTree::removeAboveExternal(const Position& p)
{
    Node* w = p.v;
    Node* v = w->par;
    Node* sib = (w==v->left ? v->right : v->left);

    if(v == _root)
    {
        _root = sib;
        sib->par=NULL;
    }
    else
    {
        Node* gpar = v->par;

        if(v == gpar->left)
            gpar->left = sib;
        else
            gpar->right = sib;

         sib->par = gpar;
    }

    delete w;
    delete v;
    n -= 2;

    return Position(sib);
}

BinaryTree::PositionList BinaryTree::positions() const
{
    PositionList pl;
    preorder(_root, pl);
    return PositionList(pl);
}
void BinaryTree::preorder(Node* v, PositionList& pl) const
{
    pl.push_back(Position(v));

    if(v->left != NULL)
        preorder(v->left, pl);

    if(v->right != NULL)
        preorder(v->right, pl);
}
void BinaryTree::preorderPrint(const BinaryTree* T, BinaryTree::Position& p)
{
    cout<<*p<<" ";

    if(!p.isExternal())
    {
        Position leftChild = p.left();
        preorderPrint(T, leftChild);

        Position rightChild = p.right();
        preorderPrint(T, rightChild);
    }
}

void BinaryTree::print(PositionList pl)
{

    for(int item = 0; item < pl.size(); item++)
    {

        BinaryTree::Position p = BinaryTree::Position(pl.at(item));

        if(p.isRoot())
            cout<<"Root: "<<*p<<endl;
        else
        {
            if(p.isExternal())
                cout<<setw(11)<<*p<<endl;
            else
                cout<<setw(9)<<*p<<endl;
        }
    }
}

// Lab exercise 2-------------------------
int BinaryTree::depth(const BinaryTree* T, const Position& p )
{
    if(p.isRoot())
        return 0;
    else
        return 1 + depth(T, p.parent());
}
//----------------------------------------
int main()
{
     BinaryTree* binT1 = new BinaryTree();
    binT1->addRoot();
    BinaryTree::Position pRoot = binT1->root();

    binT1->expendExternal(pRoot);
    BinaryTree::Position pRootLeft = pRoot.left();
    *pRootLeft = 1;
    BinaryTree::Position pRootRight = pRoot.right();
    *pRootRight = 2;

    binT1->expendExternal(pRootLeft);
    BinaryTree::Position pRootLeftLeft = pRootLeft.left();
    *pRootLeftLeft = 3;
    BinaryTree::Position pRootLeftRight = pRootLeft.right();
    *pRootLeftRight = 4;

    binT1->expendExternal(pRootRight);
    BinaryTree::Position pRootRightLeft = pRootRight.left();
    *pRootRightLeft = 5;
    BinaryTree::Position pRootRightRight = pRootRight.right();
    *pRootRightRight = 6;

    BinaryTree::PositionList pl = binT1->positions();
   
    binT1->print(pl);

	// Lab exercise 1----------------------------
    int minVal = *(pl.at(1));
    for(int item = 2; item < pl.size(); item++)
    {
        if (minVal > *(pl.at(item)))
            minVal = *(pl.at(item));

    }
	//-------------------------------------------
    int depthT = binT1->depth(binT1, pRootRightRight); // Lab exercise 2
    cout<<depthT<<endl;
    return 0;
}
