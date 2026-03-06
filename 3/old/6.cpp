#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

void buildSegmentTree(vector<int>&a, vector<int>&tree, int k, int x, int y){
    if(x==y) {
      tree[k]=a[x];
      return;
    }
    int s = (x+y)/2;
    buildSegmentTree(a,tree,2*k+1,x,s);
    buildSegmentTree(a,tree,2*k+2,s+1,y);
    //popunjavamo ostatak cvorova ali ne sabiranjem nego koji je maksimum od kog
    tree[k]=max(tree[2*k+1],tree[2*k+2]);
}

int maxElementInSegment(vector<int>& tree, int x, int y, int a, int b, int k){
  //ako nije sadrzan u segmentu
  if(x>b || y<a)
    return INT_MIN;
  //ako je u potpunosti sadrzan
  if(x>=a && y<=b)
    return tree[k];
  //inace se seku
  int s = (x+y)/2;
  return max(maxElementInSegment(tree,x,s,a,b,2*k+1),maxElementInSegment(tree,s+1,y,a,b,2*k+2));
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

  int a, b;

  std::cin >> a >> b;

  std::cout << maxElementInSegment(segment_tree, 0, n - 1, a, b, 0) << "\n";

  return 0;
}