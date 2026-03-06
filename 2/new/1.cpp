/*
za n reči nalazimo najduži prefiks

ubacujemo reči u prefiksno stablo i najduži prefiks
tražimo tako što obilazimo stablo od korena do čvora i čim naiđemo na čvor
sa dva deteta znamo da postoje barem dva odvojena prefiksa i time prekidamo traženje
tada imamo najduži prefiks
napomenimo da čvor ne mora biti list da bi bio najduži prefiks

kod prefiksnog stabla u listu se zavrsava rec, a u cvorovima sa potomcima se nastavlja
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

//za prefiksno stablo ovo su karakteristike čvora:
struct Node{
    bool isLeaf; //da li se u cvoru zavrsava rec == list -> karakteristika prefiksnog stabla
    unordered_map<char, Node*> nodes; //heš mapa gde je ključ karakter a vrednost čvor u kom je karakter
};

Node *createNode(){
    Node *newNode = new Node(); //konstruktor
    newNode->isLeaf = false; //nije list inicijalno
    return newNode;
}

//prosledjujemo adresu odakle pocinje rec da bismo joj pristupili
void addWord(Node *root, string &word, int i){
    if(i == (int)word.size()){ //ako smo dosli do kraja reči, dosli smo u tom slučaju i do lista jer se tamo reč i završava
        root->isLeaf = true;
        return;
    }
    //provera da li postoji odgovarajuce slovo odnosno da li postoji grana preko odgovarajuceg slova koja vodi do nekog novog cvora
    //ukoliko ne postoji kreiramo novu granu
    auto it = root->nodes.find(word[i]);
    if(it == root->nodes.end())
        root->nodes[word[i]] = createNode();
    addWord(root->nodes[word[i]],word,i+1);
}

void longestCommonPrefix(Node *root, string &najduziprefiks){
    //spustamo se niz stablo sve dok ne dodjemo do prvog lista i dokle god cvor ima samo jednog potomka:
    //ukoliko je list to je kraj reci
    //takodje ukoliko cvor ima dva potomka sigurno je prefiks jer se racvaju dve razlicite reci
    while(root && !root->isLeaf && root->nodes.size()==1){
        auto elem = root->nodes.begin(); //prvi i jedini elem iz mape (jer idemo dokle god imamo jednog potomka)
        najduziprefiks += elem->first; //kljuc je karakter koji dodajemo na nas string
        root = elem->second; //novi cvor koji se sad razmatra je karakter odakle pocinje nas potencijalni najduzi prefiks
    }
}

void freeTree(Node *root){
    if(root==nullptr)
        return;
    for(auto &p : root->nodes) //oslobadjamo sva podstabla
        freeTree(p.second); //zato sto je vrednost hes mape upravo cvor
    delete root;
}

int main ()
{
  vector<string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  // Probati ovaj skup reci i izbaciti uslov u petlji !root->is_leaf
  // std::vector<std::string> words = {"ana", "anastasija", "anastasijin"};

  Node *root = createNode();

  for (string &s : words)
    addWord(root, s, 0);

  string lcp = "";

  longestCommonPrefix(root, lcp);

  cout << lcp << endl;

  freeTree(root);

  return 0;
}
