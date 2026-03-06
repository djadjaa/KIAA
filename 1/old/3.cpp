#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node{
    Node(){
        left=right=nullptr;
    }
    int key;
    Node *left;
    Node *right;
};

void addNode(Node **root, int key){
    if(*root==nullptr){
        *root = new Node();
        (*root)->key = key;
        return;
    }
    if((*root)->key > key)
        addNode(&(*root)->left, key);
    else
        addNode(&(*root)->right, key);
}

void freeTree(Node *root){
    if(root==nullptr)
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

//ako nemaju svoje potomke:
bool isLeaf(Node *node){
    return (node->left == nullptr && node->right == nullptr);
}

void printPathIterative(Node *leaf_node, unordered_map<Node *, Node*> map){
    //dokle god ne dodjemo do korena ()
    while(map[leaf_node]!=nullptr){
        cout << leaf_node->key << "->";
        leaf_node = map[leaf_node]; //pomocni cvor postaje otac prethodnog pomocnog i na taj nacin idemo do korena
    }
    cout << leaf_node->key << endl;
}

void postorderIterative(Node *root){
    //formiramo stek koji cemo cuvati za smestanje obilazenih cvorova
    stack<Node *> stk;
    stk.push(root); //prvo stavljamo koren
    unordered_map<Node *, Node *> map; //mapa koja cuva cvor i njegovog roditelja
    //znamo da cvor nema roditelja:
    map[root]=nullptr;
    Node *tmp; //pomocni cvor koji ce nam sluziti za skidanje cvorova sa steka
    //dokle god imamo elemenata u steku
    while(stk.size()){
        tmp = stk.top(); //uzimam cvor sa vrha i uklanjamo ga sa steka
        stk.pop();
        //ako smo dosli do lista ispisujemo ga na standardni
        if(isLeaf(tmp))
            printPathIterative(tmp,map);
        //dodavanje levog i desnog potomka u mapu i njihovog roditelja
        if(tmp->right){
            map[tmp->right] = tmp;
            stk.push(tmp->right);
        }
        if(tmp->left){
            map[tmp->left] = tmp;
            stk.push(tmp->left);
        }
    }

}

int main()
{
  Node *root = nullptr;

  std::vector<int> keys = {4,3,5,7,1,9,8,6};

  for (int x : keys)
    addNode(&root, x);

  postorderIterative(root);

  freeTree(root);

  return 0;
}