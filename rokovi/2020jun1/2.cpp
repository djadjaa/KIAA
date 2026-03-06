//dajkstra
#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>>susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    void Dajkstra(){
        vector<int> rastojanja(V,INT_MAX);
        vector<bool> posecen(V,false);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        rastojanja[0]=0;
        pq.push({0,0});

        while(!pq.empty()){
            auto [duzina, cvor] = pq.top();
            pq.pop();

            if(posecen[cvor])
                continue;
            posecen[cvor]=true;

            for(auto [sused,suseddist] : susedi[cvor]){
                int novorast = rastojanja[cvor]+suseddist;
                if(novorast < rastojanja[sused]){
                    rastojanja[sused] = novorast;
                    pq.push({rastojanja[sused],sused});
                }
            }
        }
        int maxUdaljenost=-1, ind=-1;
        for(int i=1; i<V; i++){
            if(rastojanja[i]!=INT_MAX && rastojanja[i]>maxUdaljenost){
                maxUdaljenost = rastojanja[i];
                ind = i;
            }
        }
        cout << ind << ' ' << maxUdaljenost << endl;
    }
};

int main(){
    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v>> w;
        G->dodajGranu(u,v,w);
    }
    G->Dajkstra();
    return 0;
}