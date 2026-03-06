/*
ključno je koristiti klasične mape jer se u njih ubacuju elem po određenom poretku
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

//specifično kod prefiksnog stabla je da ne mora nužno uvek imati iste promenljive
struct Node{
    //necemo cuvati info da li smo dosli do lista vec ce sam list da cuva rec
    string wrd;
    map<char, Node*> grane;
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->wrd = "";
    return newNode;
}

void addWord(Node *root, string &wrd, int i){
    if(i==(int)wrd.size()){
        root->wrd = wrd; //tada smo dosli do lista i unosimo direkt rec u njega
        return;
    }
    auto it = root->grane.find(wrd[i]);
    if(it==root->grane.end())
        root->grane[wrd[i]]  = createNode();
    addWord(root->grane[wrd[i]],wrd,i+1);
}

void printWrds(Node *root){
    if(root->wrd != "") //izlaz iz rekurzije
        cout << root->wrd << ' ';
    //uzimamo pocetni i krajnji elem i idemo dokle god je pocetni elem postao poslednji
    auto begin = root->grane.begin();
    auto end = root->grane.end();
    while(begin!=end){
        printWrds(begin->second); //pozivamo rekurziju za odgovarajuci cvor/granu
        begin++;
    }
}

void freetree(Node *root){
    if(root==nullptr)
        return;
    for(auto &p : root->grane)
        freetree(p.second);
    delete root;
}
int main ()
{
   std::vector<std::string> words =
	 {
	 	"lexicographic", "sorting", "of", "a", "set", "of", "keys", "can",
	 	"be", "accomplished", "with", "a", "simple", "trie", "based",
	 	"algorithm", "we", "insert", "all", "keys", "in", "a", "trie",
	 	"output", "all", "keys", "in", "the", "trie", "by", "means", "of",
	 	"preorder", "traversal", "which", "results", "in", "output", "that",
	 	"is", "in", "lexicographically", "increasing", "order", "preorder",
	 	"traversal", "is", "a", "kind", "of", "depth", "first", "traversal"
	 };
  // std::vector<std::string> words = {"ana", "anastasija", "anastasijin", "anamarija", "anamarijin"};

  //std::vector<std::string> words = {"cod", "coder", "coding", "codecs"};

  Node *root = createNode();

  for (std::string &s : words)
    addWord(root, s, 0);

  printWrds(root);
  cout << endl;
  freetree(root);

  return 0;
}