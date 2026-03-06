/*
inverzija = levi u nizu je veci u odnosu na desni
preko segmentnog stabla cemo izracunati broj inverzija na sledeci nacin:
odaberemo maksimalan element i realociracemo velicinu niza na toliko
npr niz 3,4,6 ce se realocirati sa dimenzije 3 na dimenziju 6
to radimo da bismo postavili elemente na pozicije kojima odgovara
dakle element 6 cemo postaviti na poziciju 6
tacnije postavicemo 1 kao indikator da element postoji na toj poziciji i rekurzivno sabirati broj elemenata
koji su veci od njega tako sto cemo sabirati elemente koji se nalaze na segmentu od tekucielem+1 do kraja niza
a pre toga je niz inicijalizovan na 0
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int countInversionsInSegment(vector<int>&tree, int k, int x, int y, int a, int b){
    if(x>b || y<a)
        return 0;
    if(x>=a && y<=b)
        return tree[k];
    int s = (x+y)/2;
    return countInversionsInSegment(tree,2*k,x,s,a,b)+countInversionsInSegment(tree,2*k+1,s+1,y,a,b);
}

void addElementToTree(vector<int> &tree, int k, int x, int y, int i){
    if(x==y){
        tree[k]=1; //postavimo indikator da elem postoji
        return;
    }
    int s = (x+y)/2;
    if(i<=s)
        addElementToTree(tree,2*k,x,s,i);
    else
        addElementToTree(tree,2*k+1,s+1,y,i);
    //azuriranje svih cvorova
    tree[k] = tree[2*k]+tree[2*k+1];
}

int main ()
{
  std::vector<int> array = { 3, 5, 1, 4, 6, 2, 4, 7, 8, 2, 3, 4 };

  //std::vector<int> array = { 8, 4, 2, 1 };
  //std::vector<int> array = {8, 8, 4 };

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