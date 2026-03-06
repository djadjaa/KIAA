#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;
    vector<int>rastojanja;
    vector<bool>posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        rastojanja.resize(V,numeric_limits<int>::max());
        posecen.resize(V, false);
    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int Dajkstra(int u, int v){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
        rastojanja[u] = 0;
        pq.push({rastojanja[u],u});

        while(!pq.empty()){
            auto [tezinatmp,tmp] = pq.top();
            pq.pop();

            if(posecen[tmp])
                continue;
            posecen[tmp] = true;

            for(auto [sused,susedrast] : susedi[tmp]){
                int novatezina = rastojanja[tmp]+susedrast;
                if(novatezina<rastojanja[sused]){
                    rastojanja[sused] = novatezina;
                    pq.push({rastojanja[sused],sused});
                }
            }
        }

        return rastojanja[v];

    }

    void resetuj(){
        fill(rastojanja.begin(),rastojanja.end(),numeric_limits<int>::max());
        fill(posecen.begin(), posecen.end(), false);
    }

    int minRast(int A, int B, int C, int D){
        resetuj();
        int putAC = Dajkstra(A,C);
        resetuj();
        int putCB = Dajkstra(C,B);
        int putAB1 = putAC + putCB;

        resetuj();
        int putAD = Dajkstra(A,D);
        resetuj();
        int putDB = Dajkstra(D,B);
        int putAB2 = putAD + putDB;

        return min(putAB1,putAB2);
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
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << G->minRast(a,b,c,d) << endl;

    return 0;
}