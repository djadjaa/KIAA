#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*
saljemo referencu na naše segmentno drvo jer ga menjamo
kada želimo da smestimo listove pomerimo se za n mesta i upišemo elemente,a na preostala mesta do kraja od pozicije n-1
do 1 upisujemo zbir poslednja 2 lisra sve dok smo sabrali prva 2
pozicije tih zbirova su 2k i 2k+1, gde k ide od n-1 do 1

ako indeksiranje krece od 0 sabiramo elemente na pozicijama 2k+1 i 2k+2 jer koreni ćvor nam je na poziciji 0 i ako saberemo
sinove/elemente na poziciji 2k i 2k+1 elementom pozicije 2k pregazićemo naš koreni čvor/potomka
*/
void buildSegmentTree(const vector<int>&a, vector<int>&tree, int n){
    copy(begin(a),end(a),next(begin(tree),n));
    //copy_n(a.begin(),n,tree.begin()+n);
    for(int k=n-1; k>=1; k--){
        tree[k] = tree[2*k]+tree[2*k+1];
    }
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  buildSegmentTree(array, segment_tree, n);

  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";

  return 0;
}