#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool isPrime(int x){
    if(x<=1)
        return false;
    for(int i=2; i*i<=x; i++){
        if(x%i==0)
            return true;
    }
    return false;
}

void buildSegmentTree(vector<int> &a, vector<int>&tree, int k, int x, int y){
    //ubacujemo samo indikatore u zavisnosti od toga da li je broj prost ili ne
    if(x==y){
        tree[k]=a[x];
        return;
    }
    int s = (x+y)/2;
    buildSegmentTree(a,tree,2*k+1,x,s);
    buildSegmentTree(a,tree,2*k+2,s+1,y);
    tree[k] = tree[2*k+1]+tree[2*k+2];
}

int countComposite(vector<int>&tree, int x, int y, int a, int b, int k){
    if(x>b || y<a) //disjunktni
        return 0;
    if(x>=a && y<=b) //u potpunosti sadrzan
        return tree[k];
    //inace se seku
    int s = (x+y)/2;
    return countComposite(tree,x,s,a,b,2*k+1)+countComposite(tree,s+1,y,a,b,2*k+2);
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();
  
    int height = ceil(log2(n));
  
    int size = 2 * pow(2, height)-1;
  
    std::vector<int> segment_tree(size);
    
    vector<int> prime;
    for(int x:array)
        prime.push_back(isPrime(x) ? 0 : 1);
    
    for(int x:prime)
        cout << x << ' ';
    cout << endl;

    buildSegmentTree(prime, segment_tree, 0, 0 , n - 1);
  
    for (int x : segment_tree)
      std::cout << x << " ";
  
    std::cout << "\n";
  
  int a, b;

  std::cin >> a >> b;

  std::cout << countComposite(segment_tree, 0, n - 1, a, b, 0) << "\n";

  return 0;
}