/*
dato je n naslova filmova, potrebno je za svaki napraviti identifikator koji predstavlja najkraći 
prefiks naslova koji je jedinstven. ako nije moguće naći kraći od celog naslova, vratiti ceo naslov.
*/

#include <bits/stdc++.h>

using namespace std;

struct Node{
    bool isLeaf;
    unordered_map <char, Node*> children;
    int count=0;
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->isLeaf = false;
    return newNode;
}

void umetni(Node *drvo, string &s){
    for(const auto c : s){
        if(drvo->children.find(c)==drvo->children.end())
            drvo->children[c] = new Node();
        drvo = drvo->children[c];
        drvo->count++;
    }
    drvo->isLeaf=true;
}

string getPrefix(Node *drvo, const string &s){
    Node *tmp = drvo;
    string res;
    for(char c : s){
        res += c;
        tmp = tmp->children[c];
        if(tmp->count == 1)
            return res;
    }
    return s;
}

int main(){

    int n;
    cin >> n;
    cin.ignore();
    Node *drvo = createNode();
    vector<string> naslovi(n);
    for(int i=0; i<n; i++){
        getline(cin, naslovi[i]);
    }
    for(auto &s : naslovi)
        umetni(drvo,s);
    for(auto &s : naslovi){
        string prefix = getPrefix(drvo,s);
        cout << prefix << endl;
    }
    return 0;
}