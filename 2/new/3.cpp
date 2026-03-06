/*
ideja je da za svaki broj iz skupa nadjemo njegov maksimalni xor
tako sto cemo se kretati kroz taj broj bit po bit i proveriti
da li postoji njegova suprotna vrednost tako sto cemo ici granom desno
od tog bita
ono sto je zanimljivo jeste da kada se ovaj postupak ponovi za poslednji broj
dobijamo trazeni maksimalni xor za sve vrednosti
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Node{
    Node *left=nullptr;
    Node *right=nullptr;
};

void addNum(Node *root,const string &num){
    for(auto b:num){ //prolazimo kroz svaki bit
        if(b=='0'){ //levo podstablo
            if(root->left == nullptr)
                root->left = new Node();
            root = root->left;
        }else{ //desno podstablo
            if(root->right == nullptr)
                root->right = new Node();
            root = root->right;
        }
    }
}

string maxXor(Node *root,const string &binary){
    string res = "";
    for(auto b:binary){
        if(b=='0'){
            if(root->right != nullptr){ //ako postoji suprotna cifra od trenutne
                res += '1';
                root = root->right;
            }else{
                res += '0';
                root = root->left;
            }
        }else{
           if(root->left !=nullptr) { //analogno i za levo podstablo
                res += '1';
                root = root->left;
           }else{
                res += '0';
                root = root->right;
           }
        }
    }
    return res;
}

void free(Node *root){
    if(root == nullptr)
        return;
    free(root->left);
    free(root->right);
    delete root;
}

int main(void)
{
    int n; cin >> n;

    vector<string> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    Node *trie = new Node();

    auto max_binary = string(20, '0');
    for (const auto &bin_num : numbers) {
        addNum(trie, bin_num);
        auto xor_binary = maxXor(trie, bin_num);
        if (max_binary < xor_binary) {
            max_binary = xor_binary;
        }
    }
    cout << max_binary << endl;

    free(trie);

    return 0;
}