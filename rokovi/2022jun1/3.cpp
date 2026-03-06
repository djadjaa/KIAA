/*
Polazu se ispiti. Postoje zavisnosti izmedju njih. Postoji n ispita i m zavisnosti. 
Ispisati koje je sve ispite moguce poloziti kao poslednje u rastucem poretku. Slozenost O(n+m)

Primer 1:
5 4
0 1 (mora prvo 0 da se polozi pa onda 1)
2 1
1 3
3 4

Ispis:
4

Primer 2:
6 5
0 1
0 3
1 4
1 2
3 2

Ispis:
2 4 5

imamo usmeren aciklican graf, kako zelimo proveriti koje ispite poslednje polazemo, 
razmatracemo samo one cvorove ciji je izlazni stepen najmanji
odnosno nula s obzirom da ne postoje grane koje vode iz njega
*/


#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<int> outDeg;
    vector<bool> posecen;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        outDeg.resize(V,0);
        posecen.resize(V,false);
        susedi.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v); 
        outDeg[u]++;
    }

    vector<int> poslednjiIspiti(){
        vector<int> ispiti;
        for(int i=0; i<V; i++){
            if(outDeg[i]==0)
                ispiti.push_back(i);
        }
        sort(begin(ispiti),end(ispiti));
        return ispiti;
    }
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    int u,v;
    for(int i=0;i<m; i++){
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    vector<int> res = G->poslednjiIspiti();
    for(int ispit : res)
        cout << ispit << ' ';
    cout << endl;


    return 0;
}