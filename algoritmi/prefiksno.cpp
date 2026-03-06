#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    bool isLeaf=false;
    string word= "";
    int wrdlen=0;
};

void addTrie(Node *trie, string &word){
    for(char c : word){
        if(trie->children.find(c)==trie->children.end())
            trie->children[c] = new Node();
        trie = trie->children[c];
    }
    trie->isLeaf=true;
    trie->word=word;
    trie->wrdlen=(int)word.size();
}

int longestRes(Node *trie){
    int longest = trie->isLeaf ? trie->wrdlen : 0;
    for(auto &p : trie->children)
        longest = max(longest,longestRes(p.second));
    return longest;
}

int findLongest(Node *trie, string &word){
    
    for(char c : word){
        if(trie->children.find(c)==trie->children.end()){
            return 0;
        }
        trie = trie->children[c];
    }
    
    return longestRes(trie);
}

void freeTree(Node *trie){
    if(trie!=nullptr){
        for(auto &p : trie->children)
            freeTree(p.second);
        delete(trie);
    }
}

int main(){

    int n;
    cin >> n;
    Node *trie = new Node();
    string op,wrd;
    while(n--){
        cin >> op >> wrd;
        if(op=="add")
            addTrie(trie,wrd);
        else if(op=="find")
            cout << findLongest(trie,wrd) << endl;
    }
    freeTree(trie);
    return 0;
}