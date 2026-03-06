//dajkstra
#include <bits/stdc++.h>

#define INFINITY numeric_limits<int>::max()

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;
    vector<int> rastojanja;
    vector<bool> posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        rastojanja.resize(V,INFINITY);
        posecen.resize(V,false);

    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int Dajkstra(int u, int v){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        rastojanja[u] = 0;
        pq.push({rastojanja[u],u});
        while(!pq.empty()){
            auto [tezina, tmp] = pq.top();
            pq.pop();

            if(posecen[tmp])
                continue;
            posecen[tmp] = true;

            for(auto [sused,tezinasused] : susedi[tmp]){
                int novorast = tezina+tezinasused;
                if(novorast < rastojanja[sused]){
                    rastojanja[sused] = novorast;
                    pq.push({rastojanja[sused],sused});
                }
            }
        }
        return rastojanja[v]; //krajnje rastojanje
    }
    
    void reset(){
        fill(rastojanja.begin(),rastojanja.end(),INFINITY);
        fill(posecen.begin(),posecen.end(),false);
    }

    int query(int u, int v, int grad1, int grad2){
        reset();
        int u_grad1 = Dajkstra(u,grad1);
        reset();
        int grad1_v = Dajkstra(grad1, v);
        int res1 = u_grad1 + grad1_v;

        reset();
        int u_grad2 = Dajkstra(u,grad2);
        reset();
        int grad2_v = Dajkstra(grad2,v);
        int res2 = u_grad2+grad2_v;

        return min(res1,res2);
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
    cout << G->query(a,b,c,d) << endl;
    return 0;
}