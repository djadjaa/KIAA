#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void buildSegmentTree(const vector<int>&a, vector<int>&tree, int n){
    copy(begin(a),end(a),next(begin(tree),n));
    for(int k=n-1; k>=1; k--)
        tree[k]=tree[2*k]+tree[2*k+1];
}

void updateElement(vector<int>&tree, int i, int v){
    int n = tree.size()/2;
    int k = i+n; //pozicija
    tree[k] = v;
    for(k/=2; k>=1; k/=2){
        tree[k]=tree[2*k]+tree[2*k+1];
    }
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();
  
    int height = ceil(log2(n));
  
    // int size = 2 * pow(2, height);
  
    // Ukoliko indeksiranje ide od 0 imamo potrebu za jednim cvorom manje
    int size = 2 * pow(2, height);
  
    std::vector<int> segment_tree(size);
  
    // Za indeksiranje od 0 jedino sto se menja je pocetna vrednost k odnosno pozicija korenog cvora u nizu
    buildSegmentTree(array, segment_tree, n);
  
    // build_segment_tree(array, segment_tree, 1, 0 , n - 1);
  
    for (int x : segment_tree)
      std::cout << x << " ";
  
    std::cout << "\n";

  updateElement(segment_tree, 1, 3);

  for (int x : segment_tree)
      std::cout << x << " ";
  
    std::cout << "\n";

  return 0;
}