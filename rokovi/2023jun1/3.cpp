//dajkstra

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <limits>

#define INF numeric_limits<int>::max()

using namespace std;

struct compare{
    bool operator()(const pair<int,int> &p1, const pair<int,int> &p2){
        return p1.first > p2.first;
    }
};

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;
    vector<int> rastojanja;
    vector<bool>pronadjenPut;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V+1);
        rastojanja.resize(V+1,INF);
        pronadjenPut.resize(V+1,false);
    }

    void dodajGranu(int u,int v, int w){
        susedi[u].push_back(make_pair(v,w));
        susedi[v].push_back(make_pair(u,w));
    }

    int dajkstra(int u, int v){
        priority_queue<pair<int,int>,vector<pair<int,int>>, compare> hip;
        rastojanja[u] = 0;
        hip.push({rastojanja[u],u}); //mogli smo i obrnuto al ok
        while(!hip.empty()){
            auto [cena, tmp] = hip.top();
            hip.pop();
            if(pronadjenPut[tmp])
                continue;
            pronadjenPut[tmp] = true;
            if(tmp == v)
                return cena;
            for(auto [sused,susedCena]:susedi[tmp]){
                int novaCena = max(cena,susedCena);
                //u rastojanja se cuvaju cene tj tezine grana
                if(novaCena<rastojanja[sused]){
                    rastojanja[sused] = novaCena;
                    hip.push({novaCena,sused});
                }
            }
        }
        return rastojanja[v];
    }
};

int main(){
    int n,m;
    cin >> n >> m;

    Graph *G = new Graph(n);

    int u,v,w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }

    cout << G->dajkstra(1,5) << endl;

    return 0;
}