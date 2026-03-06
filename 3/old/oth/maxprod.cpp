#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

struct Node{
    int firstmax, secondmax;
};

void buildSegmentTree(vector<int>&a, vector<Node>&tree, int k, int x, int y){
    if(x==y){
        //na pocetku imamo po jedan element pa je njihov tzv par INTMIN
        tree[k].firstmax = a[x];
        tree[k].secondmax = INT_MIN;
        return;
    }
    int s = (x+y)/2;
    buildSegmentTree(a,tree,2*k,x,s);
    buildSegmentTree(a,tree,2*k+1,s+1,y);
    //popunjavanje cvorova
    tree[k].firstmax = max(tree[2*k].firstmax,tree[2*k+1].firstmax); //zato sto je secondmax intmin
    tree[k].secondmax = min(max(tree[2*k].firstmax,tree[2*k+1].secondmax),max(tree[2*k].secondmax,tree[2*k+1].firstmax));
    /*
    ako imamo 5,3 i 6,2 kad bismo poredili prvi sa prvim dobili bismo 6,3 sto ne zelimo (6,5)
    stoga radimo ovako
    */
}

Node findMaxProductInSegment(vector<Node>&tree, int k, int x, int y, int a, int b){
    Node result;
    result.firstmax = INT_MIN;
    result.secondmax = INT_MIN;
    //ukoliko su disjunktni vracamo INT_MIN
    if(a>y || b<x)
        return result;
    //ako su u potpunosti sadrzani
    if(x>=a && y<=b)
        return tree[k];
    int s = (x+y)/2;
    Node left = findMaxProductInSegment(tree,2*k,x,s,a,b);
    Node right = findMaxProductInSegment(tree,2*k+1,s+1,y,a,b);
    result.firstmax = max(left.firstmax,right.firstmax);
    result.secondmax = min(max(left.firstmax,right.secondmax),max(left.secondmax,right.firstmax));
    return result;
}

int main ()
{
  //std::vector<int> array = { 1, 3, 4, 2, 5 };
  vector<int> array = {1,2,3,4,5,6,7,8};

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<Node> segment_tree(size);

  buildSegmentTree(array, segment_tree, 1, 0, n - 1);

  for (auto x : segment_tree)
    cout << '(' << x.firstmax << ',' << x.secondmax << ')' << " ";

  std::cout << "\n";

  Node result = findMaxProductInSegment(segment_tree, 1, 0, n - 1, 0, 2);

  std::cout << result.firstmax * result.secondmax << std::endl;
  
  /*nije neophodno!!
  updateArray(array, segment_tree, 1, 6);

  result = findMaxProductInSegment(segment_tree, 1, 0, n - 1, 0, 2);

  std::cout << result.firstmax * result.secondmax << std::endl;*/

  return 0;
}