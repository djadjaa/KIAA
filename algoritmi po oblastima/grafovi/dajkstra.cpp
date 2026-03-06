#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;
    vector<bool>posecen;
    vector<int>rastojanja;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
        rastojanja.resize(V,numeric_limits<int>::max());
    }

    void dodajGranu(int u, int v,int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int dajkstra(int u, int v){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        rastojanja[u] = 0;
        pq.push({rastojanja[u],u});

        while(!pq.empty()){
            auto [tezina,tmp] = pq.top();
            pq.pop();

            if(posecen[tmp])
                continue;
            posecen[tmp] = true;
            /*
            if(tmp==v)
                return tezina;
            */
            
            for(auto [sused, susedrast] : susedi[tmp]){
                int novoRastojanje = susedrast+tezina;
                if(novoRastojanje < rastojanja[sused]){
                    rastojanja[sused] = novoRastojanje;
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
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }
    int a,b;
    cin >> a,b;
    cout << G->dajkstra(a,b) << endl;
    return 0;
}