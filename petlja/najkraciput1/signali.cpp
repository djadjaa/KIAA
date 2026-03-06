#include <bits/stdc++.h>

using namespace std;

struct comparator{
    bool operator()(const pair <int,int>&p1, const pair <int,int>&p2){
        return p1.first > p2.first;
    }
};

class Graph{
    private:
    int V;
    vector<int> rastojanja;
    vector<bool> pronadjen;
    vector<vector<pair<int,int>>> susedi;

    public:
    Graph(int V){
        this->V = V;
        rastojanja.resize(V,INT_MAX);
        pronadjen.resize(V,false);
        susedi.resize(V);
    }

    void dodajGranu(int u,int v,int w){
        susedi[u].push_back({v,w}); //jednosmerne grane, te imamo jedno push_back
    }

    void Dajkstra(int start){
        priority_queue<pair<int,int>,vector<pair<int,int>>,comparator>pq;

        rastojanja[start] = 0;
        pq.push({rastojanja[start],start});

        while(!pq.empty()){
            auto [tezina,cvor] = pq.top();
            pq.pop();

            if(pronadjen[cvor])
                continue;
            pronadjen[cvor] = true;

            for(auto [sused,tezinasused] : susedi[cvor]){
                int novatezina = tezina+tezinasused;
                if(novatezina < rastojanja[sused]){
                    rastojanja[sused] = novatezina;
                    pq.push({rastojanja[sused],sused});
                }
            }
        }
    }

    int ispisi(int start){
        Dajkstra(start);
        int res = -1;
        for(int i=0; i<V; i++){
            if(rastojanja[i]!=INT_MAX)
                res = max(res,rastojanja[i]);
        }
        return res;
    }
};
int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n+1);
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }
    int start;
    cin >> start;
    cout << G->ispisi(start) << endl;
    return 0;
}