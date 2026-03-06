#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> roditelj;
    vector<bool> posecen;
    vector<pair<int,int>> mostovi;
    vector<int> disc;
    vector<int> low;
    int discTime;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        roditelj.resize(V,-1);
        posecen.resize(V,false);
        disc.resize(V,-1);
        low.resize(V,-1);
        discTime = 0;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }
    
    void tarjan(int u){
        disc[u] = discTime++;
        low[u] = disc[u];
        posecen[u] = true;

        for(auto v : susedi[u]) {
            if(posecen[v]){
                if(roditelj[u]!=v){
                    low[u] = min(low[u],disc[v]);
                }
            }else{
                roditelj[v] = u;
                tarjan(v);
                low[u] = min(low[u],low[v]);

                if(low[v]>disc[u])
                    mostovi.push_back({u,v});
            }

        }
    }
    
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    //G->query();
    return 0;
}