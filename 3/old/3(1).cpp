#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void buildSegmentTree(const vector<int>&a, vector<int>&tree, int k, int x, int y){
    if(x==y){
        tree[k]=a[x];
        return;
    }
    int s = (x+y)/2;
    buildSegmentTree(a,tree,2*k,x,s);
    buildSegmentTree(a,tree,2*k+1,s+1,y);
    tree[k]=tree[2*k]+tree[2*k+1];
}

void updateTree(vector<int>&tree,int k,int x, int y, int i, int v){
    if(x==y)
        tree[k]=v; //azuriranje vrednosti u listu
    else{
        int s = (x+y)/2;
        if(x<=i && i<=s) //ako je potpuno sadrzan segment (dakle [x,s])
            updateTree(tree,2*k,x,s,i,v); //tada idemo u levo podstablo
        else //inace [s+1,y]
            updateTree(tree,2*k+1,s+1,y,i,v);//a inace u desno
        tree[k]=tree[2*k]+tree[2*k+1];
    }
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  buildSegmentTree(array, segment_tree, 1, 0 , n - 1);

  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";

  updateTree(segment_tree, 1, 0, n - 1, 1, 6);

  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";
  
  return 0;
}