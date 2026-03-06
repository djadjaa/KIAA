#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    string wrd = "";
    bool isLeaf;
    int counter=0;
};

void addTrie(Node *trie, string &word){
    for(char c : word){
        if(trie->children.find(c)==trie->children.end()){
            trie->children[c] = new Node();
        }
        trie = trie->children[c];
        trie->counter++;
        //cout << trie->counter << endl;
    }
    trie->wrd = word;
    trie->isLeaf=true;
}

string uniquePrefix(Node *trie, string &word){
    string res = "";
    for(char c : word){
        trie = trie->children[c];
        res+=c;
        //prvi karakter koji se pojavljuje tacno jednom, do njega imamo jedinstven prefiks
        if(trie->counter == 1)
            return res;
    }
    return word;
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

    int n;
    cin >> n;
    Node *trie = new Node();
    vector<string> words(n);
    for(int i=0; i<n; i++){
        cin >> words[i];
        addTrie(trie, words[i]);
    }
    for(int i=0; i<n; i++){
        cout << uniquePrefix(trie, words[i]) << endl;
    }

    return 0;
}