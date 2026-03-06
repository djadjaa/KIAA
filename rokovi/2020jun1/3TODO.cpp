//dopuna do palindroma
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
        if(drvo->nodes.find(c) == drvo->nodes.end())
            drvo->nodes[c] = new Node();
        drvo = drvo->nodes[c];
    }
    drvo->wrd = w;
    drvo->isLeaf = true;
}

string nadovezi(Node *drvo, string &s){
    Node *tmp = drvo;
    string res = "";
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        if(tmp->nodes.find(c)==tmp->nodes.end())
            break;
        tmp = tmp->nodes[c];
        if(tmp->isLeaf)
            res = tmp->wrd;
    }
    reverse(res.begin(),res.end());
    return res + s; //nadovezani string
}

void freeTree(Node *drvo){
    if(drvo!=nullptr){
        for(const auto &p:drvo->nodes)
            freeTree(p.second);
    }
    delete drvo;
}
/*
void print(Node *root){
    if(root->isLeaf)
        cout << root->wrd << endl;
    //prolazimo kroz sve potomke od pocetka do kraja
    auto begin = root->nodes.begin();
    auto end = root->nodes.end();
    while(begin != end){
        print(begin->second); //rekurzivni poziv za preslikanu vrednost !! (jer se kljuc slika u karakter koja se cuva)
        begin++; //sledeci potomak
    }
}*/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n;
    Node *drvo = createNode();
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        reverse(s.begin(),s.end());
        umetni(drvo,s);
    }
    //print(drvo);
    cin >> m;
    for(int i=0; i<m; i++){
        string si;
        cin >> si;
        cout << nadovezi(drvo,si) << endl;
    }
    freeTree(drvo);
    return 0;
}