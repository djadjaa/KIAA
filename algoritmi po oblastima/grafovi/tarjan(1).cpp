#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> roditelj;
    vector<bool> posecen;
    vector<bool>artikulacione;
    vector<int> disc;
    vector<int> low;
    int discTime;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        roditelj.resize(V,-1);
        posecen.resize(V,false);
        artikulacione.resize(V,false);
        disc.resize(V,-1);
        low.resize(V,-1);
        discTime = 0;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }
    
    void tarjan(int u){
        int numChilds=0;
        disc[u] = discTime++;
        low[u] = disc[u];
        posecen[u] = true;

        for(auto v : susedi[u]){
            if(posecen[v]){
                if(roditelj[u]!=v){
                    low[u] = min(low[u],disc[v]);
                }
            }else{
                numChilds++;
                //posecen[v] = true;
                roditelj[v] = u;
                tarjan(v);
                low[u] = min(low[u],low[v]);

                if(roditelj[u]!=-1 && low[v]>=disc[u])
                    artikulacione[u] = true;
            }
            if(roditelj[u]==-1 && numChilds>1)
                artikulacione[u] = true;
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