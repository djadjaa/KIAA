#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Node{
    bool isLeaf;
    unordered_map <char, Node*> grane;
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->isLeaf = false;
    return newNode;
}

void addWord(Node *root, string &wrd, int i){
    if(i==(int)wrd.size()){
        root->isLeaf = true;
        return;
    }
    auto it = root->grane.find(wrd[i]); //trazimo da li postoji grana koja cuva karakter date reci
    if(it == root->grane.end()) //ako se ne nalazi ubacujemo
        root->grane[wrd[i]] = createNode();
    addWord(root->grane[wrd[i]],wrd,i+1); //preko ove grane nastavljamo dodavanje
}

bool findWord(Node *root, string &wrd, int i){
    if(i==(int)wrd.size())
        return root->isLeaf;
    //necemo u ovom slucaju vratiti true jer ne mora nuzno znaciti da se rec iz stabla zavrsava tu
    //ako je sufiks prazan, on je u korenu akko je u korenu obelezeno da je tu kraj reci
    auto it = root->grane.find(wrd[i]);
    if(it==root->grane.end())
        return false; //reč ne postoji
    //inače rekuzrivno idemo dalje kroz granu ciji smo karakter nasli
    return findWord(root->grane[wrd[i]],wrd,i+1);
}

void freeTree(Node *root){
    if(root==nullptr)
        return; //ispraznjeno stablo
    for(auto &p : root->grane)
        freeTree(p.second);
    delete root; //zbog konstruktora
}

int main ()
{
  vector<string> words = {"cod", "coder", "coding", "codecs"};

  Node *root = createNode();

  for (string &s : words)
    addWord(root, s, 0);

  string s = "coder";

  // boolalpha nam omogucava da pisemo true i false a ne 0 ili 1
  cout << boolalpha << findWord(root, s, 0) << endl;

  freeTree(root);

  return 0;
}