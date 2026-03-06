/*
ideja je da se nadje prvo prefiks, 
uzeti cvor do kog smo stigli
i ispisati sve reci ciji se prefiks poklapa

naivna implementacija je bila iskljucivo preko mape koja je za kljuc imala prefiks a vrednost lista reci 
ciji bi im se prefiks poklapao

u ovom slucaju imacemo prefiksno stablo koje ce da cuva info o tome jesmo stigli do lista, rec koju ce taj list cuvati i mapu
gde je kljuc karakter a vrednost cvor koji cuva taj karakter

ako se poklapa cvor sa prefiksom, ispisujemo sve njegove potomke
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Node{
    bool isLeaf = false;
    string wrd = "";
    map<char, Node*> child;
};

void add(Node *root, const string &key){
    for(const auto c:key){
        //ako karakter ne postoji napraviti ga
        if(root->child.find(c)==root->child.end())
            root->child[c] = new Node();
        root = root->child[c]; //idemo dalje
    }
    //stigli smo do kraja, u listu se cuva rec !!!
    root->wrd = key;
    root->isLeaf = true; 
}


void print(Node *root){
    if(root->isLeaf)
        cout << root->wrd << endl;
    //prolazimo kroz sve potomke od pocetka do kraja
    auto begin = root->child.begin();
    auto end = root->child.end();
    while(begin != end){
        print(begin->second); //rekurzivni poziv za preslikanu vrednost !! (jer se kljuc slika u karakter koja se cuva)
        begin++; //sledeci potomak
    }
}

void autocomplete(Node *root, const string &prefix){
    for(const auto c : prefix){
        if(root->child.find(c)==root->child.end()){
            cout << -1 << endl;
            return;
        }
        root = root->child[c];
    }
    print(root);
}

void freeTree(Node *root){
    if(root == nullptr)
        return;
    for(auto &p : root->child)
        freeTree(p.second);
    delete root;
}

int main ()
{
    int n; cin >> n;

    vector<string> words(n);
    for(int i = 0; i < n; i++) {
        cin >> words[i];
    }

    string prefix; cin >> prefix;

    Node *trie = new Node();

    for (const auto &word : words) {
        add(trie, word);
    }

    autocomplete(trie, prefix);

    freeTree(trie);

    return 0;
}