#include <iostream>
#include <vector>

using namespace std;

#define MAX 100

struct Node{
    //broj pojavljivanja reda
    int count;
    //kako je matrica binarna, cvor moze imati najvise 2 potomka
    //stoga imamo binarno stablo:
    Node *nodes[2];
};

Node *createNode(){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->count = 0;
    newNode->nodes[0] = newNode->nodes[1] = nullptr;
    return newNode;
}
/*
row je red koji se dodaje, n je dimenzija reda, i je pozicija u redu
do koje smo stigli, num redni broj reda
*/
void addRow(Node *root, int row[MAX], int n, int i, int num){

}