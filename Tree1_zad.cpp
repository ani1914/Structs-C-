//Задача 1. Да се напише програма, която намира броя на срещанията на дадено число в дадено дърво от числа.
//За позиция p на дърво T, трябва да се дефинират следните методи:
//◦ p.parent() – Връща родителя на възела в позиция p;
//◦ p.children() – Връща множество с позиции на децата на възел в позиция p;
//◦ p.isRoot() – Връща true, ако възела в позиция p е корен и false в противен случай;
//◦ p.isExternal() – Връща true, ако възела в позиция p е външен и false в противен случай.
// Структурата от данни дърво осигурява следните функции:
//◦ size() – Връща броя на възлите в дървото;
//◦ empty() – Връща true, ако дървото е празно и false в противен случай;
//◦ root() – Връща позицията на корена на дървото;
//◦ position() – Връща множество с позициите на всички възли в дървото.
//◦ insert(p, e) – Вмъква елемент e в позиция p.
#include <iostream>
#include <vector>
using namespace std;

typedef int Elem;

class Tree
{
    protected:
        struct Node
        {
            Elem el;
            Node* par;
            vector<Node*> childs;

            Node()
            {
                el = 0;
                par = NULL;
            }
        };
    public:
        class Position
        {
            private:
                Node* v;
                Position(Node* u)
                { v = u; }
            public:
                Elem& operator*()
                { return v->el; }

                Position parent() const
                { return Position(v->par); }

                vector<Node*> children() const
                { return v->childs; }

                bool isRoot() const
                { return (v->par == NULL); }

                bool isExternal() const
                { return (v->childs.empty());}



                friend class Tree;
        };

        typedef vector<Position> PositionList;
        public:
            Tree();

            int size() const
            { return n; }

            bool empty() const
            { return size() == 0;}

            Position root() const
            { return Position(_root) ;}

            void addRoot()
            {
                _root = new Node();
                n = 1;
            }

            void insert(const Position& p, const Elem& e);
            PositionList position() const;
            void preorderPrint(Position&p, const Tree* T);
            void print(PositionList& pl);
        protected:
            void preorder(Node* v, PositionList& pl) const;
        private:
            Node* _root;
            int n;
};

Tree::Tree()  : _root(NULL), n(0)
{ }

void Tree::insert(const Position& p, const Elem& e)
{
    Node* parent = p.v;

    Node* v = new Node;
    v->el = e;
    v->par = parent;

    parent->childs.push_back(v);

    n++;
}

void Tree::preorder(Node* v, PositionList& pl) const
{
    pl.push_back(Position(v));
    int i = 0;

    while(i < v->childs.size())
    {
        Node* n = v->childs.at(i);

        if(n != NULL)
            preorder(n, pl);

        i++;
    }
}

Tree::PositionList Tree::position() const
{
    PositionList pl;
    preorder(_root, pl);
    return PositionList(pl);
}

void Tree::preorderPrint(Tree::Position& p, const Tree* T)
{
    cout<<*p;
    vector<Node*>ch = p.children();
    for(int i = 0; i<ch.size(); i++)
    {
        Position p = Position(ch.at(i));
        cout<<" ";
        preorderPrint(p, T);
    }
}

void Tree::print(PositionList& pl)
{
    int i = 0;
    while(i <  pl.size())
    {
        Position p = pl.at(i);
        if(p.isRoot())
            cout<<"Root: "<<*p;
        else
        {
            Position par = p.parent();
            cout<<"Parent: "<<*par;
            cout<<"Child: "<<*p;
        }
        cout<<endl;
        i++;
    }
}

int main()
{
    int x, br = 0;

    Tree* t1 = new Tree();
    t1->addRoot();

    cout<<"x=";
    cin>>x;

    t1->insert(t1->root(), 1);
    t1->insert(t1->root(), 2);
    t1->insert(t1->root(), 3);
    t1->insert(t1->root(), 4);
    t1->insert(t1->root(), 5);

    Tree::PositionList pl = t1->position();
    Tree::Position p1 = pl.at(1);

    t1->insert(p1, 52);
    t1->insert(p1, 1);
    t1->insert(p1, 3);
    t1->insert(p1, 6);

    p1 = pl.at(2);
    t1->insert(p1, 6);
    t1->insert(p1, 14);
    t1->insert(p1, 1);

    cout<<"Print tree: "<<endl;
    pl= t1->position();
    t1->print(pl);

    pl = t1->position();
    int i = 0;
    while(i < pl.size())
    {
        Tree::Position p = pl.at(i);
        if(x == (*p))
            br++;
        i++;
    }

    cout<<"br= "<<br<<endl;
    return 0;
}
