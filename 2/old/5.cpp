#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

struct Node{
    string wrd;
    int count;
    unordered_map <char, Node*> grane;
};

Node *createNode(){
    Node *newNode = new Node();
    newNode->wrd = "";
    newNode->count = 0;
    return newNode;
}

void addWrd(Node *root, string &wrd, int i){
    if(i==(int)wrd.size()){
        root->wrd = wrd;
        root->count++;
        return;
    }
    auto it = root->grane.find(wrd[i]);
    if(it == root->grane.end())
        root->grane[wrd[i]] = createNode();
    addWrd(root->grane[wrd[i]],wrd,i+1);
}

struct comparator{
    bool operator()(Node *n1, Node *n2){
        return n1->count < n2->count;
    }
};

//koristimo priority queue (hip) da bi smo sortirali cvorove na osnovu broja pojavljivanja i prvih k izvlacimo odatle
void kOccWrd(Node *root, priority_queue<Node *, vector<Node*>, comparator>&heap){
    if(root->wrd!="")
        heap.push(root); //ubacujemo rec u hip
    auto start = root->grane.begin();
    auto end = root->grane.end();
    while(start!=end){
        kOccWrd(start->second,heap);
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
  std::vector<std::string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  Node *root = createNode();

  for (std::string &s : words)
    addWrd(root, s, 0);

  /********* C++ deo *********/
  // std::priority_queue sluzi za implementaciju heap-a. Kao prvi parametarski argument (argumenti izmedju <>) dobija tip podataka koje cuva, kao drugi kolekciju koja se nalazi
  // "ispod haube", a kao treci argument dobija funkcijski objekat, funkciju i slicno sto odgovara uredjenju elemenata, tj nesto sto poredi elemente tipa koji se smestaju u heap, Node * u nasem
  // slucaju. Za vise informacija https://en.cppreference.com/w/cpp/container/priority_queue ili nakon casa mozete doci da razjasnimo
  std::priority_queue<Node *, std::vector<Node *>, comparator> heap;

  kOccWrd(root, heap);

  int k = 3;

  Node *tmp;

  while (k && heap.size())
  {
    tmp = heap.top();
    heap.pop();

    std::cout << tmp->wrd << " occurs " << tmp->count << " times " << std::endl;
    k--;
  }

  freeTree(root);
  
  return 0;
}