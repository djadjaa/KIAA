/*
Rabin Karp algoritam:
hes funkcija je sigma(karakter*256 (toliko karaktera imamo)) mod n
*/
#include <iostream>
#include <vector>

using namespace std;

//vrednost po nekom modulu
long long mod(const long long a, const long long n){
    if(a>0)
        return a%n;
    return (a%n+n)%n;
}

//stepen po modulu
long long stepenMod(long long a, long long b, const long long n){
    int d=1;
    a=mod(a,n);
    while(b>0){
        if(b&1)
            d = mod(d*a,n);
        b>>=1;
        a=mod(a*a,n);
    }
    return d;
}

//proverava stvarni sadrzaj prozora ako se heš poklopi; s i l su pomeraji
bool check(const vector<vector<char>> &text,
    const vector<vector<char>> &pattern, int s, int l){
    const int m = pattern.size();
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            if(text[i+s][j+l]!=pattern[i][j])
                return false;
        }
    }
    return true;
}

//hes vrednost za kolonu
vector<long long> hash_strips(const vector<vector<char>> &map, const int m) {
    const int n = map.size();
    vector<long long> h(n,0);
    for(int j=0; j<n; j++){
        for(int i=0; i<m; i++){
            //256 karaktera (baza), modul 257
            //h[j] = map[0][j]*d^(m-1) + map[1][j]*d^(m-2) + ... + map[m-1][j]
            h[j] = mod(mod((long long)256*h[j],(long long)257)+map[i][j],(long long)257);
        }
    }
    return h;
}
//hes vrednost za vrstu -> opsta hes vrednost
//kombinujemo heseve kolona u hes vrednost za ceo prozor
long long hash_value(const vector<long long> hash, const int m){
    long long res = 0;
    for(int j=0; j<m; j++)
    //H = h[0]*d^(m-1) + h[1]*d^(m-2) + ... + h[m-1]
        res = mod((long long)256*res+hash[j],(long long)257);
    return res;
}

bool rabinKarp(const vector<vector<char>> &tekst, const vector<vector<char>> &sablon){
    const long long n = tekst.size();
    const long long m = sablon.size();
    //faktor koji koristimo za rolling hash, njime mnozimo karakter koji izbacujemo kako bismo ga oduzeli iz trenutnog hesa
    const long long h = stepenMod((long long)256,m-1,(long long)257); //256^(m-1) mod 257
    auto hestekstKolona = hash_strips(tekst,m);
    auto hessablonKolona = hash_strips(sablon,m);
    long long hessablon = hash_value(hessablonKolona,m);
    //pomeraj:
    for(int s=0; s<n-m+1; s++){
        long long hestekst = hash_value(hestekstKolona,m);
        for(int l=0; l<n-m+1; l++){
            //ako se hes vrednosti poklapaju i njihovi karakteri zbog kolizije( da razlicite matrice daju isti hes)
            if(hessablon == hestekst && check(tekst,sablon,s,l))
                return true;
            if(l<n-m) //horizontalni pomeraj(pomeraj po kolonama fakticki)
            //azuriranje vrednosti uklanjanjem jednog od karaktera
                hestekst = mod((long long)256*(hestekst-h*hestekstKolona[l])+hestekstKolona[l+m],(long long)257);
        }
        if(s<n-m){ //vertikalni pomeraj(po vrstama)
            for(int j=0; j<n; j++)
                hestekstKolona[j] = mod((long long)256*(hestekstKolona[j]-h*tekst[s][j])+tekst[s+m][j],(long long)257);
        }
    }
    return false;
}

int main(){

    int n,m;
    cin >> n >> m;

    vector<vector<char>> tekst(n,vector<char>(n));
    vector<vector<char>> sablon(m,vector<char> (m));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> tekst[i][j];
        }
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            cin >> sablon[i][j];
        }
    }

    if(rabinKarp(tekst,sablon))
        cout << "da\n";
    else
        cout << "ne\n";

    return 0;
}