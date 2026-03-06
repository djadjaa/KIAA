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
    vector<bool> artikulacione;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
        disc.resize(V,-1);
        low.resize(V,-1);
        roditelj.resize(V,-1);
        artikulacione.resize(V,false);
        discoveryTime=0;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }
    
    void Tarjan(int u){
        int numChilds=0;
        posecen[u] = true;
        disc[u] = discoveryTime++;
        low[u] = disc[u];

        for(auto sused : susedi[u]){
            if(posecen[sused]){
                //ako sused nije potomak
                if(roditelj[u]!=sused)
                    low[u] = min(low[u],disc[sused]);
            }else{
                numChilds++;
                //sused jeste potomak
                roditelj[sused] = u;
                Tarjan(sused);
                
                low[u] = min(low[u],low[sused]);

                //ako cvor nije koren drveta
                if(roditelj[u]!=-1 && low[sused]>=disc[u])
                    artikulacione[u] = true;
            }
            //ako smo u korenu
            if(roditelj[u]!=-1 && numChilds>1)
                artikulacione[u] = true;
        }
    }
    void query(){
        Tarjan(0);
        for(int i=0; i<artikulacione.size(); i++){
            if(artikulacione[i])
                cout << i << ' ';
        }
        cout << endl;
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