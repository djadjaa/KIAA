#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node *grane[4];
};

Node *createNode(){
    Node *newNode = new Node();
    fill(newNode->grane, newNode->grane+4,nullptr);
    return newNode;
}

void ubaci(Node *drvo, const string &s, int i){
    Node *cvor = drvo;
    while(i<s.length()){
        if(cvor->grane[s[i]-'a']==nullptr)
            cvor->grane[s[i]-'a'] = createNode();
        cvor = cvor->grane[s[i]-'a'];
        i++;
    }
}

int numSubStr(Node *drvo){
    if(drvo==nullptr)
        return 0;
    int num = 1;
    for(int i=0; i<4; i++)
        num += numSubStr(drvo->grane[i]);
    return num;
}

void freeT(Node *drvo){
    if(drvo!=nullptr){
        for(int i=0; i<4; i++)
            freeT(drvo->grane[i]);
        delete drvo;
    }
}

int main(){

    string s;
    cin >> s;
    Node* koren = createNode();
    for (size_t i = 0; i < s.length(); i++)
        ubaci(koren, s, i);
    cout << numSubStr(koren) << endl;
    freeT(koren);

    return 0;
}