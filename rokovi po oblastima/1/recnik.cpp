#include <bits/stdc++.h>
using namespace std;

struct Node{
    unordered_map<char,Node*> children;
    string wrd;
    bool isLeaf;
    int counter;
};

void addTrie(Node *trie, string &wrd){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            trie->children[c] = new Node();
        trie = trie->children[c];
        trie->counter++;
    }
    trie->wrd = wrd;
    trie->isLeaf = true;
}

bool searchWrd(Node *trie, string &wrd){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            return false;
        trie = trie->children[c];
    }
    return trie->isLeaf;
}

bool startsWith(Node *trie, string &wrd, int n){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            return false;
        n--;
        if(n==0)
            return true;
        trie = trie->children[c];
    }
    return false;
}

int countWrd(Node *trie){
    int count = 0;
    //baza rekurzije
    if(trie->isLeaf)
        count++;
    for(auto &child : trie->children)
        count += countWrd(child.second);

    return count;
}

//autocomplete
int commonPrefix(Node *trie, string &wrd){
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end()){
            return 0;
        }
        trie = trie->children[c];
    }
    return countWrd(trie);
}

string longest(Node *trie, string &wrd){
    string res="";
    string tmp="";
    for(char c:wrd){
        if(trie->children.find(c)==trie->children.end())
            break;

        trie = trie->children[c];
        tmp+=c;

        if(trie->isLeaf)
            res = tmp;
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

    int q;
    cin >> q;
    char c;
    string str;
    Node *trie = new Node();
    while(q--){
        cin >> c;
        if(c=='I'){ //insert
            cin >> str;
            addTrie(trie,str);
        }else if(c=='S'){ //search
            cin >> str;
            cout << (searchWrd(trie,str) ? "da\n" : "ne\n");
        }else if(c=='P'){ //prefix
            cin >> str;
            int vel = str.size();
            cout << (startsWith(trie,str,vel) ? "da\n" : "ne\n");
        }
        else if(c=='C'){ //count
            cin >> str;
            cout << commonPrefix(trie,str) << endl;
        }
        else if(c=='L'){ //longest common prefix
            cin >> str;
            cout << longest(trie,str) << endl;
        }
    }
    freeTrie(trie);
    return 0;
}