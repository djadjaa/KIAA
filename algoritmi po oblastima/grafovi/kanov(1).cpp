#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool>posecen;
    vector<int> inDeg;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
        inDeg.resize(V,0);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        inDeg[v]++;
    }

    void Kanov(){
        queue<int> q;
        for(int i=0; i<V; i++){
            if(inDeg[i]==0)
                q.push(i);
        }

        while(!q.empty()){
            int tmp = q.front();
            q.pop();

            //query

            for(int sused : susedi[tmp]){
                inDeg[sused]--;
                if(inDeg[sused]==0)
                    q.push(sused);
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
    G->Kanov();
    return 0;
}