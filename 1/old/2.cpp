#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node{
    Node(){
        left = right = nullptr;
    }
    int key;
    Node *left;
    Node *right;
};

void addNode(Node **root, int key){
    if(*root == nullptr){
        *root = new Node();
        (*root)->key = key;
        return;
    }
    if((*root)->key > key)
        addNode(&(*root)->left,key);
    else
        addNode(&(*root)->right,key);
}

void freeTree(Node *root){
    if(root == nullptr)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void printTree(Node *root){
    if(root==nullptr)
        return;
    printTree(root->left);
    printTree(root->right);
    cout << root->key << " ";
}

void postorderIterative(Node *root){
    //stek sa inicijalnim cvorovima stabla
    stack<Node *>stk;
    stk.push(root);
    //stek u kom se cuvaju cvorovi u redosledu DLK (desno levo koren)
    stack<int> out;
    while(!stk.empty()){
        //uzimamo cvor sa vrha steka
        Node *curr = stk.top();
        //brisemo cvor sa vrha
        stk.pop();
        //isti taj cvor stavljamo na stek za ispis
        out.push(curr->key);
        //na inicijalni stek stavljamo kako levog tako desnog potomka
        if(curr->left)
            stk.push(curr->left);
        if(curr->right)
            stk.push(curr->right);
    }
    while(!out.empty()){
        cout << out.top() << " ";
        out.pop();
    }
    stk.push(root);
}

int main()
{
  Node *root = nullptr;

  std::vector<int> keys = {4,3,5,7,1,9,8,6};

  for (int x : keys)
    addNode(&root, x);

  printTree(root);

  std::cout << std::endl;

  postorderIterative(root);

  std::cout << std::endl;

  freeTree(root);

    return 0;
}