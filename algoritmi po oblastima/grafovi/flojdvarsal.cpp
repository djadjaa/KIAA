#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        for(int i=0; i<V; i++)
            susedi[i].resize(V,0);
    }

    void dodajGranu(int u, int v,int w){
        susedi[u][v] = w;
        susedi[v][u] = w;
    }

    void flojd(){
        for(int k=0; k<V; k++){
            for(int i=0; i<V; i++){
                for(int j=0; j<V; j++){
                    susedi[i][j] = max(susedi[i][j], susedi[i][k]+susedi[k][j]);
                }
            }
        }
        for(int i=0; i<V; i++){
            for(int j=0; j<V; j++){
                cout << susedi[i][j] << ' ';
            }
            cout << endl;
        }
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
    G->flojd();
    return 0;
}