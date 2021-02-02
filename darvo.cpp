 /*
 p.parent() – Връща родителя на възела в позиция p;
◦ p.children() – Връща множество с позиции на децата на възел в позиция p;
◦ p.isRoot() – Връща true, ако възела в позиция p е корен и false в противен случай;
◦ p.isExternal() – Връща true, ако възела в позиция p е външен и false в противен случай.
 Структурата от данни дърво осигурява следните функции:
◦ size() – Връща броя на възлите в дървото;
◦ empty() – Връща true, ако дървото е празно и false в противен случай;
◦ root() – Връща позицията на корена на дървото;
◦ position() – Връща множество с позициите на всички възли в дървото.
◦ insert(p, e) – Вмъква елемент e в позиция p.
*/

#include <iostream>
#include <vector>
using namespace std;

typedef int Elem;

class Tree {
protected:
struct Node
{
    Elem el;
    Node* par;
    vector<Node*>childs;

    Node(){
        el=0;
        par=NULL;
    }
};

public:
class Position{
   
    public:
    Elem& operator*(){
        return v->el;
    }
    Position parent() const{
        return Position(v->par);
    }
    vector<Node*>children() const{
        return v->childs;
    }
    bool isRoot() const{
        return (v->par==NULL);
    }
    bool isExternal()const{
        return (v->childs.empty());
    }
   
    friend class Tree;
   
     private:
    Node* v;
    Position (Node* u)
    {v=u;}
    
};
typedef vector<Position> PositionList;
public:
Tree();

int size() const
{return n;}

bool empty()const
{return size()==0;}
 Position root() const { //връща корена на дървото
        return Position (_root);
    }

void addRoot(){
    _root=new Node();
    n=1;
}

void insert(const Position& p, const Elem& e);
PositionList position() const;
void print (PositionList& pl);
void preorderPrint(Position& p, const Tree* T);



protected:
void preorder(Node* v, PositionList& pl) const;
private:
Node* _root;
int n;


};

Tree::Tree():_root(NULL), n(0){}

void Tree::insert(const  Position& p, const Elem& e){
    Node* parent=p.v;

    Node* v=new Node;
    v->el=e;
    v->par=parent;

    parent->childs.push_back(v);

    n++;
}

Tree::PositionList Tree::position() const{
    PositionList pl;
    preorder(_root,pl);
    return PositionList(pl);
}
void Tree::preorder (Node* v, PositionList& pl) const{
    pl.push_back(Position(v));
    int i=0;
    
    while (i<v->childs.size())
    {
        Node* n=v->childs.at(i);
        if(n!=NULL)
            preorder(n,pl);
            i++;
        

    }
    
}
void Tree::print(PositionList& pl){
    int i=0;
    while (i<pl.size())
    {
        Position p= pl.at(i);
        if(p.isRoot())
        cout<<"Root: "<<*p;
        else{
            Position par=p.parent();
            cout<<"Parent: "<<*par;
            cout<<" Child:"<<*p;
        }
        cout<<endl;
        i++;
    }
    
}

void Tree:: preorderPrint( Tree:: Position& p, const Tree* T){
    cout<<*p;
    vector<Node*>ch=p.children();
    for(int i=0; i<ch.size();i++){
        Position p=Position(ch.at(i));
        cout<< " ";
        preorderPrint(p,T);
    }
}

int main(){
    int x, br=0;
    Tree* tl=new Tree(); //create Tree
    tl->addRoot(); // добавя корен към дървото -> 1 възел засега и това е корена 

    tl->insert(tl->root(),1); // вмъкваме наследници 
    tl->insert(tl->root(),2); // вмъкваме наследници 
    tl->insert(tl->root(),3); // вмъкваме наследници 
    tl->insert(tl->root(),4); // вмъкваме наследници 
    tl->insert(tl->root(),5); // вмъкваме наследници 

    Tree::PositionList pl=tl->position(); //all naslednici na korena 
    Tree::Position pl=p1.at(1);
    tl->insert(pl,50);
    cout<<"Print tree: "<<endl;
    pl=tl->position();
    tl->print(p1);
    return 0;
}