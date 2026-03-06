#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void buildSegmentTree(vector<int> &a, vector<int>& tree, int k, int x, int y) {
    if(x==y){
        //ubacujemo indikatore ako je broj paran
        if(a[x]%2==0)
            tree[k] = 1;
        else
            tree[k] = 0;
        return;
    }
    int s = (x+y)/2;
    buildSegmentTree(a,tree,2*k+1,x,s);
    buildSegmentTree(a,tree,2*k+2,s+1,y);
    tree[k]=tree[2*k+1]+tree[2*k+2];
}

int countEvenElements(vector<int>&tree, int x, int y, int a, int b, int k){
    //disjunktni
    if(x>b || y<a)
        return 0;
    //u potpunosti sadrzani
    if(x>=a && y<=b)
        return tree[k];
    //presek
    int s = (x+y)/2;
    return countEvenElements(tree,x,s,a,b,2*k+1)+countEvenElements(tree,s+1,y,a,b,2*k+2);
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  // Ukoliko indeksiranje ide od 0 imamo potrebu za jednim cvorom manje
  int size = 2 * pow(2, height) - 1;

  std::vector<int> segment_tree(size);

  buildSegmentTree(array, segment_tree, 0, 0, n - 1);
  
  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";
  int a, b;

  std::cin >> a >> b;

  std::cout << countEvenElements(segment_tree, 0, n - 1, a, b, 0) << "\n";

  return 0;
}