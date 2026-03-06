#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char,Node*> children;
    bool isLeaf;  
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->isLeaf = true;
    return newNode;
}

void ubaci(Node *drvo, const string &w, int i=0){
    if(i==w.size()){
        drvo->isLeaf = true;
        return;
    }
    auto it = drvo->children.find(w[i]);
    if(it==drvo->children.end())
        drvo->children[w[i]] = new Node();
    ubaci(drvo->children[w[i]],w,i+1);
}

bool izbaci(Node *drvo, const string &w, int i=0){
    //ako je drvoprazno, ono je uspesno obrisano
    if(drvo == nullptr)
        return true;
    if(i==w.length())
        drvo->isLeaf = false;
    else{
        auto it = drvo->children.find(w[i]);
        if(it!=drvo->children.end() && izbaci(it->second,w,i+1))
            drvo->children.erase(it);
    }
    
    //ako imamo barem jedan prazan cvor
    if(!drvo->isLeaf && drvo->children.size()==0){
        delete drvo;
        return true; //uspesno obrisano
    }else
        return false; //nije ipak
}

void freeT(Node *drvo){
    if(drvo!=nullptr){
        for(const auto &p : drvo->children)
            freeT(p.second);
    }
    delete drvo;
}

bool sadrzi(Node *drvo, const string &w, int i=0){
    if(drvo == nullptr)
        return false;
    if(i==w.size())
        return drvo->isLeaf;
    auto it = drvo->children.find(w[i]);
    if(it!=drvo->children.end())
        return sadrzi(it->second,w,i+1);
    return false;
}

Node* izbaciCvor(Node* drvo, const string& w) {
    if (izbaci(drvo, w, 0))
      return nullptr;
    else
      return drvo;
  }

int main(){

    ios_base::sync_with_stdio(false); cin.tie(0);
  
  Node* koren = createNode();
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string naredba, niska;
    cin >> naredba >> niska >> ws;
    if (naredba == "ubaci")
      ubaci(koren, niska);
    else if (naredba == "izbaci")
        koren = izbaciCvor(koren, niska);
    else if (naredba == "trazi") {
      if (sadrzi(koren, niska))
        cout << "da" << "\n";
      else
        cout << "ne" << "\n";
    }
  }
  freeT(koren);

    return 0;
}