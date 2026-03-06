#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node *grane[10];
    bool isLeaf;
};

Node *createNode(){
    Node *newNode = new Node();
    fill(newNode->grane,newNode->grane+10,nullptr);
    newNode->isLeaf = false;
    return newNode;
}

bool ubaci(Node *drvo, const string &s){
    Node *cvor = drvo;
    bool indikator=false;
    for(char c:s){
        if(cvor->isLeaf)
            return false;
        if(cvor->grane[c-'0']==nullptr){
            indikator = true;
            cvor->grane[c-'0'] = createNode();
        }
        cvor = cvor->grane[c-'0'];
    }
    if(!indikator)
        return false;
    cvor->isLeaf=true;
    return true;
}

void obrisi(Node *drvo){
    if(drvo!=nullptr){
        for(auto it : drvo->grane)
            obrisi(it);
        delete drvo;
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    bool OK = true;
    string broj;
    Node* koren = createNode();
    for (int i = 0; i < n; i++) {
        cin >> broj;
        if (OK && !ubaci(koren, broj))
            OK = false;
    }
    if (OK)
        cout << "da" << endl;
    else
        cout << "ne" << endl;
    obrisi(koren);

    return 0;
}