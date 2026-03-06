#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool>posecen;
    vector<int> disc;
    vector<int> low;
    vector<int> roditelj;
    int discoveryTime;
    vector<pair<int,int>> mostovi;


    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
        disc.resize(V,-1);
        low.resize(V,-1);
        roditelj.resize(V,-1);
        discoveryTime=0;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void tarjanMost(int u){
        posecen[u] =true;
        disc[u] = discoveryTime++;
        low[u] = disc[u];
        for(int v : susedi[u]){
            if(posecen[v]){
                if(roditelj[u]!=v)
                    low[u] = min(low[u],disc[v]);
            }else{
                roditelj[v] = u;

                tarjanMost(v);

                low[u] = min(low[u],low[v]);

                if(low[v]>disc[u])
                    mostovi.push_back({u,v});
            }
        }
    }

    void query(){
        tarjanMost(0);
        for(auto &p : mostovi)
            cout << p.first << ' ' << p.second << endl;
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
    G->query();
    return 0;
}