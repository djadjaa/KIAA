#include <bits/stdc++.h>
using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    bool isLeaf;
    string str="";
    int counter=0;
};

//dodaj rec
void addTrie(Node *trie, string &wrd){
    for(auto c : wrd){
        if(trie->children.find(c)==trie->children.end())
            trie->children[c] = new Node();
        trie = trie->children[c];
        trie->counter++;
    }
    trie->isLeaf = true;
    trie->str = wrd;
}

//potrazi da li se nalazi u drvetu
bool search(Node *trie, string &wrd){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            return false;
        trie = trie->children[c];
    }
    return trie->isLeaf;
}

//da li pocinje rec sa datim prefiksom
bool startsWith(Node *trie, string &wrd, int n){
    for(char c : wrd){
        if(trie->children.find(c)== trie->children.end())
            return false;
        n--;
        if(n==0)
            return true;
        trie = trie->children[c];
    }
    return false;
}

//prebroj reci
int countWrds(Node *trie){
    int count = 0;

    if(trie->isLeaf)
        count++;
    for(auto &child : trie->children)
        count += countWrds(child.second);
    return count;
}

//prebroj reci koje imaju zajednicki prefiks
int commonPrefix(Node *trie, string &wrd){
    for(char c : wrd){
        if(trie->children.find(c)==trie->children.end())
            return 0;
        trie = trie->children[c];
    }
    return countWrds(trie);
}

//najduzi prefiks
string longest(Node *trie, string &wrd){
    string res = "";
    string tmp = "";
    for(char c : wrd){
        if(trie->children.find(c)==trie->children.end())
            break;
        trie = trie->children[c];
        tmp += c;
        if(trie->isLeaf)
            res = tmp;
    }
    return res;
}

//oslobodi drvo
void freeTrie(Node *trie){
    if(trie!=nullptr){
        for(auto &p : trie->children)
            freeTrie(p.second);
        delete(trie);
    }
}

int main(){

    //query operations

    return 0;
}