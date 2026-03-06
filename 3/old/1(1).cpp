#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
a je inicijalni niz, k je pozicija cvora unutar niza, x i y su krajevi intervala

kod rekurzivne implementacije prosledjujemo indeks od kog krecemo i  levu i desnu granicu niza koji razmatramo

od korena se spustamo skroz levo pa desno od prvog potomka i kada im dodamo rvednosti idemo ka njihovom roditelju
i azuriramo njegovu vrednost
dakle, redosled je: levo->desno->potomak i to odozdo ka gore
ne mozemo dodeliti vrednost roditelju dok ne dodelimo vrednost njegovim sinovima
dakle, na osnovu rekurzivnih poziva izvlačimo elemente niza koje smeštamo u novi niz ako je dimenzija niza 1, 
potom roditelja dobijamo sabiranjem sinova
*/
void buildSegmentTreeAlternative(vector<int>&a, vector<int>&tree, int k, int x, int y){
    /*ako su granice jednake(odnosno da li smo dosli do samo 1 elem) taj elem smestamo u niz, 
    zavrsava se za levu polovinu a započinje se rek poziv za desnu
    kada smestimo potomke vracamo se na roditelje*/
    if(x==y){
        tree[k]=a[x];
        return;
    }
    //napravimo sredisnji indeks
    int s = (x+y)/2; 
    //slicna prica kao kod merge sorta
    //sinovi tekuceg potomka su na tim pozicijama (2k+1 i 2k+2) (ovo su nova k u odnosu na roditelja)
    //levo podstablo:
    buildSegmentTreeAlternative(a,tree,2*k+1,x,s);
    //desno podstablo:
    buildSegmentTreeAlternative(a,tree,2*k+2,s+1,y);
    tree[k] = tree[2*k+1]+tree[2*k+2];

    /*
    da ne pocinje indeksiranje od nule bilo bi:
    
    buildSegmentTreeAlternative(a,tree,2*k,x,s);
    buildSegmentTreeAlternative(a,tree,2*k+1,s+1,y);
    tree[k] = tree[2*k]+tree[2*k+1];
    */
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5 };

  int n = array.size();

  int height = ceil(log2(n));

  // int size = 2 * pow(2, height);

  // Ukoliko indeksiranje ide od 0 imamo potrebu za jednim cvorom manje
  int size = 2 * pow(2, height) - 1;

  std::vector<int> segment_tree(size);

  // Za indeksiranje od 0 jedino sto se menja je pocetna vrednost k odnosno pozicija korenog cvora u nizu
  buildSegmentTreeAlternative(array, segment_tree, 0, 0 , n - 1);

  // build_segment_tree(array, segment_tree, 1, 0 , n - 1);

  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";

  return 0;
}