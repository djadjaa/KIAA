#include <bits/stdc++.h>

using namespace std;

struct Node{
      bool isLeaf=false;
      unordered_map<char, Node*> children;
      string wrd = "";
};

void addTrie(Node *node, string &s){
      for(char c : s){
            if(node->children.find(c)==node->children.end())
                  node->children[c] = new Node();
            node = node->children[c];
      }
      node->isLeaf = true;
      node->wrd = s;
}

bool slozena(Node *trie, string &word,int index, int count){
      for(int i=index; i<word.length(); i++){
            //ako rec ne postoji
            if(trie->children.find(word[i])==trie->children.end())
                  return false;
            trie = trie->children[word[i]];
            //ako smo dosli do lista:
            if(trie->isLeaf){
                  //i ako smo dosli do kraja reci
                  if(i == word.length()-1)
                        //proveravamo da li imamo vise od jedne prostih koje formiraju slozenu
                        return count >= 1;
                  
                  if(slozena(trie,word,index+1,count+1))
                        return true;
            }
      }
      return false;
}

int main(){
      int n;
      cin >> n;
      vector<string> words(n);
      Node *node = new Node();
      for(int i=0; i<n; i++){
            cin >> words[i];
            addTrie(node, words[i]);
      }
      for(auto &s : words){
            if(slozena(node,s,0,0))
                  cout << s << ' ';
      }

      return 0;
}