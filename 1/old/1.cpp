/*
za dato binarno stablo pretrage ispisati njegov spiralni obilazak po nivoima
            1
        /        \
      2           3
     /\           /\
    4  5         6  7
za ovo stablo moze biti:
-sdesna nalevo: 1 3 2 4 5 6 7
-sleva nadesno: 1 2 3 7 6 5 4
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Node{
    Node(){
        left = right = nullptr;
    }
    int key;
    Node *left; //levi potomak
    Node *right; //desni potomak
};
/*
Koristimo pokazivač na pokazivač (Node** root) zato što želimo da modifikujemo sam pokazivač root unutar funkcije, 
a ne samo vrednost na koju pokazuje.
Normalno, kada koristimo pokazivač (Node* root), on sadrži adresu čvora.
Međutim, ako želimo izmeniti tu adresu unutar funkcije (tj. promeniti root tako da pokazuje na novi čvor), moramo proslediti njegovu adresu 
– što znači pokazivač na pokazivač (Node** root).
Ako bismo koristili Node* root, funkcija bi radila sa kopijom pokazivača. Promene napravljene na root unutar funkcije 
ne bi uticale na originalni pokazivač izvan funkcije.

ako bismo imali sledecu definiciju fje:
void add_node(Node *root, int key)

i sve ostane isto, napravice se kopija pokazivaca koji ce pokazivati na novoformirani cvor
a mi zelimo da napravimo pokazivac koji ce da pokazuje na pokazivac koji bi trebalo da pokazuje na novoformirani cvor

zato imamo 2 zvezdice
*/
void addNode(Node **root, int key){
    if(*root == nullptr){//ako smo se spustili do kraja niza odnosno poslednjeg potomka
        *root = new Node();//automatski se alocira memorija za nas cvor i inicijalizuje levi i desni pokazivac na null
        (*root)->key = key;//dodeljivanje vrednosti kljuca
        return;
    }
    if((*root)->key > key)
        addNode(&(*root)->left,key);
    else
        addNode(&(*root)->right,key);
}

void freeTree(Node *root){
    if(root==nullptr) //nema sta da praznimo
        return;
    //oslobadjamo podstabla
    freeTree(root->left);
    freeTree(root->right);
    delete root; //brisemo koren, radimo delete jer konstruktor sam automatski alocira memoriju inace bismo morali da radimo free
}

void printTree(Node *root){
    if(root==nullptr)
        return; //nema sta da ispisujemo
    printTree(root->left); //ispisujemo levo podstablo
    printTree(root->right); //analogno i desno podstablo
}

//u zavisnosti od toga ocemo zdesna ili zdesna da ispisemo bice nam true ili false
void spiralTraversal(Node *root, bool leftToRight){
    list<Node*> nodes; //moze i deque
    nodes.push_back(root); //najpre dodajemo koren
    //kako krecemo od korena odmah cemo promeniti vrednost flega
    leftToRight = !leftToRight;
    //u tom slucaju cemo zaista posle korena ici sleva na desno

    while(nodes.size()){ //dokle god postoji tzv sinhronizacija liste/reda sa stablom
        int n = nodes.size(); //trenutni br elem
        while (n){
            //ako idemo sleva nadesno tada skidamo element sa pocetka a stavljamo na kraj
            if(leftToRight){
                Node *tmp = nodes.front();
                nodes.pop_front();
                n--;
                cout << tmp->key << " ";
                //ako cvor ima levog potomka
                if(tmp->left)
                    nodes.push_back(tmp->left);
                //a zatim i ako cvor ipak ima desnog potomka
                if(tmp->right)
                    nodes.push_back(tmp->right);
            }else{ //inace obrnuto
                Node *tmp = nodes.back();
                nodes.pop_back();
                n--;
                cout << tmp->key << " ";
                //ovde je obrnuto jer postavljamo element na pocetak
                if(tmp->right)
                    nodes.push_front(tmp->right);
                if(tmp->left)
                    nodes.push_front(tmp->left);
            }
        }

        leftToRight=!leftToRight; //menjanje strane
        cout << "\n";
    }
}

int main(){

    Node *root = nullptr;
    vector<int> keys = {4,3,5,7,1,9,8,6};
    for(int x : keys)
        addNode(&root,x);
    spiralTraversal(root,true);
    freeTree(root);

    return 0;
}