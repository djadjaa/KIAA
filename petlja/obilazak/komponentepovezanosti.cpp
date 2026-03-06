#include <bits/stdc++.h>

using namespace std;

struct Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void dfs(vector<vector<int>>&susedi, vector<int>&komponente, int cvor, int k){
        komponente[cvor] = k;
        for(int sused : susedi[cvor])
            if(komponente[sused]==0)
                dfs(susedi, komponente, sused, k);
    }

    void komponente(){
        vector<int> komponente(V,0);
        int id = 0;
        for(int i=0; i<V; i++)
            if(komponente[i]==0)
                dfs(susedi, komponente, i, ++id);
        
        for(auto x : komponente)
            cout << x << ' ';
        cout<< endl;
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
    G->komponente();
    return 0;
}