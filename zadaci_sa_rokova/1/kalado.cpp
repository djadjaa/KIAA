#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    string wrd = "";
    bool isLeaf;
};

void addTrie(Node *trie, string &word){
    for(char c : word){
        if(trie->children.find(c)==trie->children.end()){
            trie->children[c] = new Node();
        }
        trie = trie->children[c];
    }
    trie->wrd = word;
    trie->isLeaf=true;
}

bool kalado(Node *trie, string &word, int d){
    for(char c : word){
        //ako ne postoji karakter u drvetu
        if(trie->children.find(c)==trie->children.end())
            return false;
        d--;
        //ako smo dosli do kraja 'prefiksa' i svi karakteri su 'na mestu'
        if(d==0){
            return true;
        }
        trie = trie->children[c];
    }
    //inace ne postoji takav prefiks
    return false;
}

void freeTree(Node *trie){
    if(trie!=nullptr){
        for(auto &p : trie->children){
            freeTree(p.second);
        }
        delete(trie);
    }
}

int main(){

    int n,m;
    cin >> n >> m;
    Node *trie = new Node();
    vector<string> words(n);
    for(int i=0; i<n; i++){
        cin >> words[i];
        addTrie(trie, words[i]);
    }
    string s;
    int d;
    while(m--){
        cin >> s >> d;
        cout << (kalado(trie,s,d) ? '1' : '0') << endl;
    }
    return 0;
}