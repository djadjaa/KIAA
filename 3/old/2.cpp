#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

void buildSegmentTree(const vector<int>&a, vector<int>&tree, int n){
    copy(begin(a),end(a),next(begin(tree),n));
    //copy_n(a.begin(),n,tree.begin()+n);
    for(int k=n-1; k>=1; k--){
        tree[k] = tree[2*k]+tree[2*k+1];
    }
}

int sumOfSegment(const vector<int>&tree, int a, int b){
    int n = tree.size()/2;
    //pozicije drveta
    a+=n;
    b+=n;
    cout << a << ' ' << b << endl;
    int sum = 0;
    while(a<=b){
        //ako je levi kraj segmenta desno dete(neparna pozicija)
        if(a%2==1){
            sum += tree[a++]; //pomeranje u levo
            cout << sum << endl;
        }
        //ako je desni kraj segmenta levo dete(parna pozicija)
        if(b%2==0){
            sum += tree[b--]; //pomeranje u desno
            cout << sum << endl;
        }
        //penjanje na nivo iznad
        a/=2;
        b/=2;
        //cout << sum << ' ' << endl;
        cout << a << ' ' << b << endl;
    }
    return sum;
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

  cout << sumOfSegment(segment_tree, 1, 3) << endl;

  return 0;
}