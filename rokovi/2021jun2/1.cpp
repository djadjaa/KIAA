//imenik
#include <bits/stdc++.h>

using namespace std;

struct Node{
    bool isLeaf;
    unordered_map<char, Node*> nodes;
    string wrd="";
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->isLeaf = false;
    return newNode;
}

void umetni(Node *drvo, const string &w){
    for(const auto c:w){
        if(drvo->nodes.find(c)==drvo->nodes.end())
            drvo->nodes[c] = new Node();
        drvo = drvo->nodes[c];
    }
    drvo->wrd = w;
    drvo->isLeaf = true;
}

int maxWrd(Node *drvo){
    int maxLen = drvo->isLeaf ? (int)drvo->wrd.size() : 0;
    for(auto &p : drvo->nodes)
        maxLen = max(maxLen,maxWrd(p.second));
    return maxLen;
}

int najduzeIme(Node *drvo, const string &prefix){
    for(const auto c : prefix){
        if(drvo->nodes.find(c)==drvo->nodes.end())
            return 0;
        drvo = drvo->nodes[c];
    }
    return maxWrd(drvo);
}

void freeTree(Node *drvo){
    if(drvo!=nullptr){
        for(const auto &p : drvo->nodes)
            freeTree(p.second);
    }
    delete drvo;
}

int main(){
    int n;
    cin >> n;
    string upit,ime;
    Node *node = createNode();
    while(n--){
        cin >> upit >> ime;
        if(upit == "add"){
            umetni(node,ime); //ubacujemo celo ime a ne karakter pa nemamo nikakav indeks
        }else if(upit=="find"){
            cout << najduzeIme(node,ime) << endl;
        }
    }
    freeTree(node);
    return 0;
}