#include <bits/stdc++.h>

using namespace std;

int code(char c){
    switch(c){
        case 'c':
            return 0;
        case 't':
            return 1;
        case 'g':
            return 2;
        case 'a':
            return 3;
    }
    return -1;
}

struct Node{
    Node *grane[4];
    int numPrefix;
};

Node *createNode(){
    Node *newNode = new Node();
    fill(newNode->grane,newNode->grane+4,nullptr);
    newNode->numPrefix=0;
    return newNode;
}

void ubaci(Node *drvo, string &s){
    Node *cvor = drvo;
    for(char c:s){
        if(cvor->grane[code(c)]==nullptr){
            cvor->grane[code(c)]=createNode();
        }
        cvor = cvor->grane[code(c)];
        cvor->numPrefix++;
    }
}

int numPrefix(Node *drvo, string &s){
    Node *cvor = drvo;
    for(char c:s){
        if(cvor->grane[code(c)]==nullptr)
            return 0;
        cvor = cvor->grane[code(c)];
    }
    if(cvor==nullptr)
        return 0;
    return cvor->numPrefix;
}

void freeT(Node *cvor){
    if(cvor!=nullptr){
        for(Node *c : cvor->grane)
            freeT(c);
        delete cvor;
    }
}

int main(){

    ios_base::sync_with_stdio(false); cin.tie(0);
  // prefiksno drvo u kome se cuvaju ucitane niske i broje prefiksi
    Node* drvo = createNode();
    // ucitavamo jednu po jednu nisku do kraja ulaza
    string niska;
    while (cin >> niska) {
        // ispisujemo broj niski u drvetu kojima je tekuca niska prefiks
        cout << numPrefix(drvo, niska) << '\n';
        // ubacujemo novu nisku u drvo
        ubaci(drvo, niska);
    }
    // brisemo prefiksno drvo
    freeT(drvo);

    return 0;
}