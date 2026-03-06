#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Node{
    bool isLeaf;
    unordered_map<char,Node *> grane;
};

Node* createNode(){
    Node *newNode = new Node();
    newNode->isLeaf = false;
    return newNode;
}

void addWord(Node *root, string &wrd, int i){
    if(i==(int)wrd.size()){
        root->isLeaf = true;
        return;
    }
    auto it = root->grane.find(wrd[i]);
    if(it==root->grane.end())
        root->grane[wrd[i]] = createNode();
    addWord(root->grane[wrd[i]],wrd,i+1);
}

void LCP(Node *root, string &lcp){
    //ukoliko je list to je kraj reci; takodje ukoliko cvor ima dva potomka sigurno je prefiks jer se racvaju dve razlicite reci
    while(root && !root->isLeaf && root->grane.size()==1){ //spustamo se niz stablo sve dok ne dodjemo do prvog lista i dokle god cvor ima samo jednog potomka:
        auto elem = root->grane.begin();
        lcp += elem->first; //dodajemo karakter na string koji je kljuc
        root = elem->second; //novi cvor kroz koji prolazimo
    }
}

void freeTree(Node *root){
    if(root == nullptr)
        return;
    for(auto &p : root->grane)
        freeTree(p.second);
    delete root;
}

int main ()
{
  /*vector<string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};*/

  // Probati ovaj skup reci i izbaciti uslov u petlji !root->is_leaf
  vector<string> words = {"ana", "anastasija", "anastasijin"};

  Node *root = createNode();

  for (string &s : words)
    addWord(root, s, 0);

  string lcp = "";

  LCP(root, lcp);

  cout << lcp << endl;

  freeTree(root);

  return 0;
}