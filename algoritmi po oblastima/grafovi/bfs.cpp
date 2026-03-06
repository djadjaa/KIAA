#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool>posecen;
    vector<int> bfsDrvo;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
    }

    void bfs(int u){
        queue<int> q;
        posecen[u] = true;
        q.push(u);
        while(!q.empty()){
            int tmp = q.front();
            q.pop();

            bfsDrvo.push_back(tmp);

            for(int sused : susedi[tmp]){
                if(posecen[sused])
                    continue;
                posecen[sused] = true;
                q.push(sused);
            }
        }
        for(int x : bfsDrvo)
            cout << x << ' ';
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
    G->bfs(0);

    return 0;
}