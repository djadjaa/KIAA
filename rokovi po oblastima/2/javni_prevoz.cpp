//dajkstra
#include <bits/stdc++.h>

#define INFINITY numeric_limits<int>::max()

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;
    vector<int> rastojanja;
    vector<bool> posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        rastojanja.resize(V,INFINITY);
        posecen.resize(V,false);

    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int Dajkstra(int u,int v){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        rastojanja[u] = 0;
        pq.push({rastojanja[u],u});

        while(!pq.empty()) {
            auto [tezina, tmp] = pq.top();
            pq.pop();
            if(posecen[tmp])
                continue;
            posecen[tmp] = true;
            /*
            Ako ideš:
            sa stanice A (čija je cena c[A])
            na stanicu B (čija je cena c[B])
            onda ne plaćaš c[B], nego:

            max(0, c[B] − c[A])

            Znači:

            ako je B „skuplja zona“ → platiš razliku
            ako je B „jeftinija ili ista“ → vožnja je besplatna
            
            Plaćaš samo kada prvi put podižeš maksimum:
            */
            for(auto [sused,tezinasused] : susedi[tmp]){
                int cena = tezinasused < tezina ? 0 : (tezinasused-tezina);
                int novatezina = tezina+cena; 
                //Cena ne zavisi od dužine puta, nego samo od najveće cene stanice do koje si došao
                if(novatezina < rastojanja[sused]){
                    rastojanja[sused] = novatezina;
                    pq.push({rastojanja[sused],sused});
                }

            }
        }
        return rastojanja[v];

    }
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n+1);
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }
    cout << G->Dajkstra(1,n) << endl;
    return 0;
}