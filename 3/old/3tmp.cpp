#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// najmanji stepen dvojke veci ili jednak od n
int stepenDvojke(int n) {
  int s = 1;
  while (s < n)
    s <<= 1;
  return s;
}

// na osnovu datog niza a dužine n u kom su elementi smešteni od
// pozicije 0 formira se segmentno drvo i elementi mu se smeštaju u
// niz drvo krenuvši od pozicije 1
vector<int> formirajSegmentnoDrvo(const vector<int>& a) {
  int n = stepenDvojke(a.size());
  vector<int> drvo(2*n, 0);
  // kopiramo originalni niz u listove (u niz drvo, od pozicije n nadalje)
  copy(begin(a), end(a), next(begin(drvo), n));
  // ažuriramo roditelje već upisanih elemenata
  for (int k = n-1; k >= 1; k--)
    drvo[k] = drvo[2*k] + drvo[2*k+1];
  return drvo;
}

// izračunava se zbir elemenata polaznog niza dužine n koji se 
// nalaze na pozicijama iz segmenta [a, b] na osnovu segmentnog drveta
// koje je smešteno u nizu drvo, krenuvši od pozicije 1
int zbirSegmenta(const vector<int>& drvo, int a, int b) {
  int n = drvo.size() / 2;
  a += n; b += n;
  int zbir = 0;
  // sve dok je segment neprazan
  while (a <= b) {
    // ako je levi kraj segmenta desno dete, dodajemo ga posebno u zbir
    if (a % 2 == 1) zbir += drvo[a++];
    // ako je desni kraj segmenta levo dete, dodajemo ga posebno u zbir
    if (b % 2 == 0) zbir += drvo[b--];
    // penjemo se na nivo iznad, na roditeljske cvorove
    a /= 2;
    b /= 2;
  }
  return zbir;
}

// ažurira segmentno drvo smešteno u niz drvo od pozicije 1
// koje sadrži elemente polaznog niza a dužine n u kom su elementi
// smešteni od pozicije 0, nakon što se na poziciju i polaznog
// niza upiše vrednost v
void upisi(vector<int>& drvo, int i, int v) {
  int n = drvo.size() / 2;
  // prvo ažuriramo odgovarajući list
  int k = i + n;
  drvo[k] = v;
  // ažuriramo sve roditelje izmenjenih čvorova
  for (k /= 2; k >= 1; k /= 2)
    drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  vector<int> drvo = formirajSegmentnoDrvo(a);
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    string upit;
    cin >> upit;
    if (upit == "p") {
      int i, v;
      cin >> i >> v >> ws;
      upisi(drvo, i, v);
    } else if (upit == "z") {
      int a, b;
      cin >> a >> b;
      cout << zbirSegmenta(drvo, a, b) << '\n';
    }
  }
  return 0;
}