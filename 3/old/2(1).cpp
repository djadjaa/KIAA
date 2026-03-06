#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

void buildSegmentTree(const vector<int>& a, vector<int>&tree, int k, int x, int y){
    if(x==y){
        tree[k] = a[x];
        return;
    }
    int s = (x+y)/2;
    buildSegmentTree(a,tree,2*k,x,s);
    buildSegmentTree(a,tree,2*k+1,s+1,y);
    tree[k]=tree[2*k]+tree[2*k+1];
}

int sumOfSegment(vector<int>& tree, int k, int x, int y, int a, int b){
    //ako su disjkunktni, dakle ne poklapaju se tekuci i dati segment
    if(b<x || a>y)
        return 0;
    //ako su u potpunosti sadrzani, to znaci da smo dosli do elementa
    if(x>=a && y<=b)
        return tree[k];
    //inace se seku te cemo ici u levo podstablo odn desno da dodjemo do elementa
    int s = (x+y)/2;
    return sumOfSegment(tree,2*k,x,s,a,b)+sumOfSegment(tree,2*k+1,s+1,y,a,b);
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  buildSegmentTree(array, segment_tree, 1, 0 , n - 1);

  std::cout << sumOfSegment(segment_tree, 1, 0, n-1, 1, 3) << "\n";

  return 0;
}