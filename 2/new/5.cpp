/*
0 1 1 1 0
1 0 0 1 0
1 0 1 1 1
1 1 1 0 1
0 0 0 1 1

|
|
V

0 1 1 1 0
1 1 1 1 0
1 1 1 1 1
1 1 1 1 1
0 0 0 1 1

radicemo uniju disjunktnih skupova: skup nula koje su opkoljene jedinicama i skup onih nula koje nisu

primetimo da su samo nule koje su opkoljene jedinicama postale jedinice
dok nule koje se nalaze skroz gore i skroz dole nisu

dakle: ukoliko se nula nalazi na prvoj ili poslednjoj koloni odn prvoj ili poslednjoj vrsti
radimo uniju skupa sa tom nulom i nulama koje nisu opkoljene jedinicama
inace suprotno, tj unija nule i elementima na pozicijama (i,j+1), (i, j-1), (i-1,j) i (i+1,j) (4 str)

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> parent; //znamo da podskupove cuvamo u obliku drveta tako da sesvaki elem slika u njegovog roditelja u drvetu
vector<int> rang;

void init(int n){
    parent.resize(n);
    rang.resize(n);

    for(int i=0; i<n; i++){
        parent[i]=i;
        rang[i]=0;
    }
}

int find(int x){
    while(x!=parent[x]){
        parent[x]=parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }
    init(n*m+1);
}