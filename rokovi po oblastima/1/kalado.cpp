#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    bool isLeaf;
    string wrd;
};

void addTrie(Node *trie, string &wrd){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            trie->children[c] = new Node();
        trie = trie->children[c];
    }
    trie->isLeaf = true;
    trie->wrd = wrd;
}

bool trieQuery(Node *trie, string &wrd, int x){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            return false;
        x--;
        if(x==0)
            return true;
        trie = trie->children[c];
    }
    return false;
}

void freeTrie(Node *trie) {
    if(trie!=nullptr){
        for(auto &p : trie->children)
            freeTrie(p.second);
        delete(trie);
    }
}

int main(){
    int n,q;
    cin >> n >> q;
    vector<string> words(n);
    Node *trie = new Node();
    for(int i=0; i<n; i++){
        cin >> words[i];
        addTrie(trie,words[i]);
    }
    string strquery;
    int x;
    while(q--){
        cin >> strquery >> x;
        cout << trieQuery(trie,strquery,x) << endl;
    }
    freeTrie(trie);
    return 0;
}