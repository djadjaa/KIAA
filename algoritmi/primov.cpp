#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v,int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }
    int primov(){
        int ukRast = 0;
        vector<bool> mst(V, false);
        vector<int> rastojanja(V,INFINITY);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>>pq;

        for(int i=0; i<V; i++){
            if(!mst[i]){
                rastojanja[i] = 0;
                pq.push({i,rastojanja[i]});

                while(!pq.empty()){
                    auto [tmp,tmptezina] = pq.top();
                    pq.pop();

                    if(mst[tmp])
                        continue;
                    mst[tmp] = true;

                    ukRast += rastojanja[i];

                    for(auto &[sused,susedtezina] : susedi[tmp]){
                        if(!mst[sused] && susedtezina < rastojanja[sused]){
                            rastojanja[sused] = susedtezina;
                            pq.push({sused,rastojanja[sused]});
                        }
                    }
                }
            }
        }
        return ukRast;
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
    cout << G->primov() << endl;
    return 0;
}
