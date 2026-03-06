#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    bool isLeaf;
    string wrd = "";

    int counter = 0;
};

void addTrie(Node *trie, string &wrd){
    for(char c: wrd){
        if(trie->children.find(c)==trie->children.end())
            trie->children[c] = new Node();
        trie = trie->children[c];
        trie->counter++;
        cout << trie->counter << endl;
    }
    trie->isLeaf = true;
    trie->wrd = wrd;
}

string uniquePrefix(Node *trie, string &wrd){
    string res="";

    for(char c:wrd){
        trie = trie->children[c];
        res+=c;
        if(trie->counter==1)
            return res;
    }

    return res;
}

void freeTrie(Node *trie){
    if(trie!=nullptr){
        for(auto &p : trie->children)
            freeTrie(p.second);
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
        addTrie(trie,words[i]);
    }
    for(int i=0; i<n; i++)
        cout << uniquePrefix(trie, words[i]) << endl;
    freeTrie(trie);
    return 0;
}