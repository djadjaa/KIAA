/*
za složenost reči proveravamo na sledeći način:

fja prima koren prefiksnog stabla, reč koju proveravamo trenutno, indeks karaktera u reči do kog se stiglo
i broj reči iz rečnika koje su se javile unutar prefiksa reči koja se pretražuje

ako za trenutni karakter ne postoji odgovarajuća grana zaključujemo da
ta reč nije složena
ako naiđemo na čvor u kom se završava neka reč tada postoji šansa da sadrži nadovezanu reč
tada pokrećemo funkciju ponovo sa pomerenim indeksom i uvećanim brojem reči
takođe ako naiđemo na čvor u kom se završava neka reč ALI je brojač karaktera za jedan manji od dužine reči koju proveravamo
i broj reči je veći od jedan, tada smo na putu ka tome da pronađemo složenu reč

-----------------------------------------------

tldr: proveravamo da li je prefiks slozene reci upravo rec iz recnika i da li se upravo ta slozena rec nalazi u recniku
ako se ne nalazi, rekurzivno idemo na poziciju posle prefiksa 
medjutim kako ce ovo biti slozenost O(brreci), efikasnije je proveriti da li se karakter koji cini jednu od proste reci nalazi u slozenoj i ako dodjemo
do proste reci, nasli smo slozenu rec

npr catsdogcat
stigli smo do cat, koji se nalazi u recniku, ali se u recniku ne nalazi sdogcat
medjutim ako bismo dosli do cats koji se nalazi u recniku,  kako znamo da se i dog i cat nalaze u recniku, time cemo zakljuciti da je to slozena rec
*/

#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Node{
    bool isLeaf=false;
    unordered_map<char,Node *> children;
};

/*
!!! DRUGI NACIN !!!

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
*/

void addNode(Node *root, const string &key){
    for(const auto c:key){
        if(root->children.find(c)==root->children.end()){ //ako ne postoji karakter u nasem prefiksnom stablu
            root->children[c]= new Node(); //formiranje
        }
        root = root->children[c]; //tekući čvor koji je sad koren sledeće reči
    }
    root->isLeaf = true; //ako smo došli do lista, to i naglasimo bool vrednošću
}

bool is_compound_word(Node *root, const string &word, const int indeks, const int brojac){
    Node *node = root;
    for(int i=indeks; i<word.length(); i++){
        //(izlazak iz rekurzije)
        //Ako trenutni karakter ne postoji u stablu, nema reči koja počinje ovim delom
        if(node->children.find(word[i])==node->children.end()){
            return false;
        }
        node = node->children[word[i]]; //prelazimo na sledeći potomak
        //ako smo dosli do lista
        if(node->isLeaf){
            //i ako smo došli do kraja originalne reči
            if(i==word.length()-1)
                return brojac >= 1; // i do sada našli barem jednu celokupnu reč
                //tada imamo složenu reč
            if(is_compound_word(root,word,i+1,brojac+1))//inače rekurzivno proveravamo ostatak reči od sledeće pozicije i povećavamo broj pronađenih reči
                return true;
        }
    }
    return false;
}

void freeTree(Node *root){
    if(root==nullptr)
        return;
    for(auto &p : root->children)
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

    Node *trie = new Node();

    for (const auto &word : words) {
        addNode(trie, word);
    }

    set<string> compound_words;
    for (const auto &word : words) {
        if (is_compound_word(trie, word, 0, 0)) {
            compound_words.insert(word);
        }
    }

    for (const auto &word : compound_words) {
        cout << word << " ";
    }
    cout << endl;

    free(trie);

    return 0;
}