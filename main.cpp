#include <fstream>
//#include <iostream>
//Am avut de implementat Pairing Heap, si l-am rezolvat cu 100 de puncte pe Infoarena
using namespace std;

std::ifstream cin("mergeheap.in");
std::ofstream cout("mergeheap.out");

class node{
    int val;
    node* copil, *frate;

public:
    int getVal() const {
        return val;
    }

    void setVal(int val) {
        node::val = val;
    }

    node *getCopil() const {
        return copil;
    }

    void setCopil(node *copil) {
        node::copil = copil;
    }

    node *getFrate() const {
        return frate;
    }

    void setFrate(node *frate) {
        node::frate = frate;
    }

    node(int v):val(v),copil(nullptr),frate(nullptr){}

    void addcopil(node *nd){
        if(nd== nullptr)return;
        if(copil== nullptr){
            copil = nd;
            return;
        }
        node* aux = copil;
        while(aux->frate!= nullptr){
            aux= aux->frate;
        }
        aux->frate=nd;
    }
};
class pheap{
    node *root;
public:
    pheap(){root= nullptr;}
    pheap(int x){root= new node(x);}

    void push(int val){
        if(root==nullptr){
            root = new node(val);
            return;
        }
        node *aux = new node(val);
        if(root->getVal() < val)
            swap(root, aux);
        aux->setFrate(root->getCopil());
        root->setCopil(aux);
    }
    void merge(pheap &B){
        if(B.root == nullptr)return;
        if(root == nullptr){
            swap(root,B.root);
            return;
        }
        if(B.root->getVal()>root->getVal()){
            swap(root,B.root);
        }
        B.root->setFrate(root->getCopil());
        root->setCopil(B.root);
        B.root = nullptr;
    }
    static node * merge_pairs(node * nod){
        if(nod == nullptr || nod->getFrate() == nullptr)return nod;
        pheap p1,p2,p3;
        node *urm;
        p1.root = nod;
        p2.root = nod->getFrate();
        urm = nod->getFrate()->getFrate();
        p1.merge(p2);
        p3.root = merge_pairs(urm);
        p1.merge(p3);
        return p1.root;
    }
    int toppop() {
        int rez = root->getVal();
        node *rt = root;
        if(root->getCopil()== nullptr)root = nullptr;
        else root = merge_pairs(root->getCopil());
        delete rt;
        return rez;
    }
};

int main() {
    int n,q;
    cin>>n>>q;
    pheap *h = new pheap[n];
    for(int i=0;i<q;i++){
        int querry;
        cin>>querry;
        switch(querry){
            case 1:{
                int m,x;
                cin>>m>>x;
                h[m-1].push(x);
                break;
            }
            case 2:{
                int m;
                cin>>m;
                cout<<h[m-1].toppop()<<"\n";
                break;
            }
            case 3:{
                int a,b;
                cin>>a>>b;
                h[a-1].merge(h[b-1]);
                break;
            }
            default:{}
        }
    }
    delete[] h;
    return 0;
}
