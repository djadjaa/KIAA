#include <bits/stdc++.h>

using namespace std;

struct Graph{
    private:
    vector<vector<int>> susedi;
    int n,m;
    long long cenaServera, cenaKompa;

    public:
    Graph(int n,int m,
        long long cenaServera, int cenaKompa){

        this->n=n;
        this->m=m;
        this->cenaServera=cenaServera;
        this->cenaKompa = cenaKompa;

        susedi.resize(n);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }



    
};

int main(){

    long long cenaServera, cenaKompa;
    cin >> cenaServera >> cenaKompa;
    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n,m,cenaServera,cenaServera);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    return 0;
}