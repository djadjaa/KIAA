#include <bits/stdc++.h>

using namespace std;

struct Node{
    unordered_map<char,Node*> children;
    bool isLeaf;
    string str="";
    int counter=0;
};

void addTrie(Node *trie, string &st){
    for(char c : st) {
        if(trie->children.find(c)== trie->children.end())
            trie->children[c] = new Node();
        trie = trie->children[c];
        trie->counter++;
    }
    trie->isLeaf = true;
    trie->str = st;
}

bool searchWrd(Node *trie, string &st){
    for(char c : st){
        if(trie->children.find(c)==trie->children.end())
            return false;
        trie = trie->children[c];
    }
    return trie->isLeaf;
}

bool startsWith(Node *trie, string &st, int stsize){
    for(char c:st){
        if(trie->children.find(c)==trie->children.end())
            return false;
        stsize--;
        if(stsize==0)
            return true;
        trie = trie->children[c];
    }
    return false;
}

//najduzi prefiks
//#TODO
void freeTrie(Node *trie){
    if(trie!=nullptr){
        for(auto &p : trie->children)
            freeTrie(p.second);
        delete(trie);
    }
}

int main(){



    return 0;
}