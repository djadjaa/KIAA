/*DRUGI NACIN samo umesto postojanja pokazivaca imacemo niz dimenzije 2 i procenjujemo na osnovu pozicija i njihove suprotne vr */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Node{
    bool isLeaf;
    Node *nodes[2];
};

Node *createNode(){
    Node *newNode = (Node *)malloc(sizeof(Node)); //alociramo jer imamo pokazivac na niz duzine 2
    newNode->isLeaf = false;
    newNode->nodes[0] = newNode->nodes[1] = nullptr;
    return newNode;
}

int value(string &binary){
    int n = binary.size();
    int value = 0;
    for(int i=0, j=n-1; i<n; i++,j--)
        value += pow(2,i)*(binary[j]-'0');
    return value;
}

void addNum(Node *root, string &num, int i){
    if(i==(int)num.size()){//ako smo stigli do kraja broja
        root->isLeaf = true;//stigli smo i do lista
        return;//rekurzivni poziv; baza indukcije
    }
    //ako nemamo odgovarajuci cvor, kreiramo ga
    //kako bismo dobili zaista 0 ili 1, oduzimamo sa '0'
    if(root->nodes[num[i]-'0']==nullptr)
        root->nodes[num[i]-'0'] = createNode();
    addNum(root->nodes[num[i]-'0'],num,i+1); //rekurzivno nastavljamo za ostatak broja
}

void findXOR(Node *root, string &res, string &num, int i){
    if(root->isLeaf)
        return; //baza indukcije
    int digit = num[i] - '0';
    if(root->nodes[abs(digit-1)]){ //da li postoji cvor koji cuva cifru suprotnu od ite cifre broja num
        res += '1';
        findXOR(root->nodes[abs(digit-1)],res,num,i+1); //rekurzivno idemo dalje
        //idemo u pravcu gde je tekuca cifra
    }else{
        res += '0';
        findXOR(root->nodes[digit],res,num,i+1);
    }
}

void freeTree(Node *root){
    if(root==nullptr)
        return;
    for(auto &node:root->nodes)
        freeTree(node);
    free(root);
}

int main ()
{
  vector<string> numbers = {"101", "000", "011"};

  int max = 0;
  string max_XOR;

  string XOR;

  Node *root = createNode();

  for (string &s : numbers) {
    XOR = "";
    addNum(root, s, 0);

    findXOR(root, XOR, s, 0);

    if (value(XOR) > max) {
      max = value(XOR);
      max_XOR = XOR;
    }
  }

  cout << max_XOR << endl;

  freeTree(root);

  return 0;
}