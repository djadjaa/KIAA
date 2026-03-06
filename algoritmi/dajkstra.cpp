#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>>susedi;
    vector<int> rastojanja;
    vector<bool> posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        rastojanja.resize(V,numeric_limits<int>::max());
        posecen.resize(V,false);
    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int Dajkstra(int u, int v){
        int cena;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
        rastojanja[u] =0;
        pq.push({rastojanja[u],u});

        while(!pq.empty()){
            auto [tezina,tmp] = pq.top();
            pq.pop();

            if(posecen[tmp])
                continue;
            posecen[tmp] = true;

            for(auto [sused,susedtezina] : susedi[tmp]){
                if(susedtezina < rastojanja[tmp])
                    cena = 0;
                else
                    cena = susedtezina - rastojanja[tmp];

                int novatezina = rastojanja[tmp]+cena;
                if(novatezina < rastojanja[sused]){
                    rastojanja[sused] = novatezina;
                    pq.push({rastojanja[sused],sused});
                }
                //cout << "res: " << novatezina << endl;
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