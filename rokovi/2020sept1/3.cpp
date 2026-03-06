#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int dest;
    int w;
    int id;
};

class Graph{
    private:
    int V,E;
    vector<vector<Edge>>susedi;

    public:
    Graph(int V, int E){
        this->V = V;
        this->E = E;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, int w, int id){
        susedi[u].push_back({v,w,id});
        susedi[v].push_back({u,w,id});
    }

    long long dfs(){
        vector<bool> posecen(V,false);
        vector<bool> poseceneGrane(E,false);

        long long res = 0;

        //bfs:
        queue<int> q;
        q.push(0);
        posecen[0]=true;

        while(!q.empty()){
            int tmp = q.front();
            q.pop();

            for(auto &sused : susedi[tmp]){
                //ignorisemo negativne grane
                if(sused.w < 0)
                    continue;
                //ako grana nije posecena, dodajemo je na rezultat
                if(!poseceneGrane[sused.id]){
                    res += sused.w;
                    poseceneGrane[sused.id]=true;
                }
                //sused nam je posecen
                if(!posecen[sused.dest]){
                    q.push(sused.dest);
                    posecen[sused.dest]=true;
                }
            }
        }
        return res;
    }
};

int main(){
    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n,m);
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w,i);
    }
    cout << G->dfs() << endl;
    return 0;
}