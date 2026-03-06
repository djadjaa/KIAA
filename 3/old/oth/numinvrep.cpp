#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int countInversionsInSegment(vector<int>&tree, int k, int x, int y, int a, int b){
    //disjunktni
    if(x>b || y<a)
        return 0;
    //u potpunosti sadrzani
    if(x>=a && y<=b)
        return tree[k];
    int s = (x+y)/2;
    return countInversionsInSegment(tree,2*k,x,s,a,b)+countInversionsInSegment(tree,2*k+1,s+1,y,a,b);
}

void addElementToTree(vector<int>&tree, int k, int x, int y, int i){
    if(x==y){
        tree[k] += 1; //kod ponavljanja cemo samo dodavati jedinice (ako nema bice svakako jedinica jer je inicijalizovan niz na 0)
        return;
    }
    int s = (x+y)/2;
    //levo podstablo
    if(i<=s)
        addElementToTree(tree,2*k,x,s,i);
    else
        addElementToTree(tree,2*k+1,s+1,y,i);
    tree[k] = tree[2*k]+tree[2*k+1];
}

int main ()
{
 // std::vector<int> array = { 3, 5, 1, 4, 6, 2, 4, 7, 8, 2, 3, 4 };

 // std::vector<int> array = { 8, 4, 2, 1 };
  std::vector<int> array = {8, 8, 4 };

  int n = array.size();

  //odaberemo maksimalni elem
  int max = *std::max_element(array.begin(), array.end());

  //tzv realokacija dimenzije
  int height = ceil(log2(max));

  int size = 2 * pow(2, height);

  //inicijalizacija
  std::vector<int> segment_tree(size, 0);

  int result = 0;

  for (int i = 0; i < n; i++) {
      //sabiramo koliko ima elemenata vecih od tekuceg od samog sledbenika do kraja niza
      //a u stablu su uveliko
      result += countInversionsInSegment(segment_tree, 1, 1, max, array[i] + 1, max);
      //zatim dodajemo sledeci prisutan elem (moze i obrnuti poredak)
      addElementToTree(segment_tree, 1, 1, max, array[i]);
      //primetimo da je u argumentu array[i] da se on tumaci kao pozicija
  }

  std::cout << result << std::endl;

  return 0;
}