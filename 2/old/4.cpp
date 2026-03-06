#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Node{
    string wrd; //opet u listu cuvamo rec a ne info da li smo dosli do lista
    int count; //br pojavljivanja reci
    unordered_map<char, Node*> grane;
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->wrd= "";
    newNode->count = 0;
    return newNode;
}

void addWrd(Node *root, string &wrd, int i){
    if(i==(int)wrd.size()){
        root->count++;
        root->wrd = wrd;
        return;
    }
    auto it = root->grane.find(wrd[i]);
    if(it==root->grane.end())
        root->grane[wrd[i]] = createNode();
    addWrd(root->grane[wrd[i]],wrd,i+1);
}

/*
saljemo referencu na max to nam je kao globalna promenljiva - direktno pristupamo njoj tj
njenoj adresi i menjamo vr pri svakom rekurzivnom pozivu
da nemamo referencu, promenljiva max bi sve vreme bila 0 i pravile bi se sve vreme kopije koje se samo nece uzimati u obzir
i ostala bi vrednost maksimuma ista; u tom slucaju ce se promeniti vrednost maksimuma na poslednjem rekurzivnom pozivu te se moze desiti da se azurira
na vrednost koju ne bi trebalo
stoga mora referenca da bi smo direktno azurirali vrednost
*/
void maxOcc(Node *root, string &maxOccWrd, int &max){
    if(root->wrd != ""){
        //cout << root->wrd << " " << max << endl;
        if(root->count > max){
            max = root->count;
            maxOccWrd = root->wrd;
        }
    }
    auto start = root->grane.begin();
    auto end = root->grane.end();
    while(start!=end){
        maxOcc(start->second, maxOccWrd, max);
        start++;
    }
}

void freeTree(Node *root){
    if(root==nullptr)
        return;
    for(auto &p : root->grane)
        freeTree(p.second);
    delete root;
}

int main ()
{
  // std::vector<std::string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
	// 	"codeless", "codec", "codecs", "codependence", "codex", "codify",
	// 	"codependents", "codes", "code", "coder", "codesign", "codec",
	// 	"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  // Obrisati & kod &max u funkciji find_max_occuring_word i pokrenuti sa ovim skupom reci
  // std::vector<std::string> words = {"anamarija", "anastasija", "anastasija"};

  std::vector<std::string> words = {"cod", "codecs", "coding", "coder", "coding", "coder", "coding"};

  Node *root = createNode();

  for (std::string &s : words)
    addWrd(root, s, 0);

  std::string most_occurences_word = "";

  int max = 0;

  maxOcc(root, most_occurences_word, max);

  std::cout << most_occurences_word << std::endl;

  freeTree(root);
  
  return 0;
}