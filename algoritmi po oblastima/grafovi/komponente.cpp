#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool>posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void komponenteDFS(int u, vector<int> &komponente, int komponentaID){
        komponente[u] = komponentaID;
        for(int sused : susedi[u]){
            if(komponente[sused]==0)
                komponenteDFS(sused,komponente,komponentaID);
        }
    }
    
    int query(){
        vector<int> komponente(V,0);
        int komponentaID = 0;
        for(int i=0; i<V; i++){
            if(komponente[i]==0){
                komponenteDFS(i,komponente,++komponentaID);
            }
        }
        return komponentaID; //zvanicna vrednost je upravo broj komponenti
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
    cout << G->query() << endl;
    return 0;
}