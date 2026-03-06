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

    int primov(int k){
        vector<bool> mst(V,false);
        vector<int> rastojanja(V,numeric_limits<int>::max());
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        vector<int> res;
        for(int start=0; start<V; start++){
            if(!mst[start]){
                rastojanja[start]=0;
                pq.push({rastojanja[start],start});
                while(!pq.empty()){
                    int tmp = pq.top().second;
                    int tmp_tezina = pq.top().first;
                    pq.pop();
                    if(mst[tmp])
                        continue;
                    mst[tmp] = true;
                    if(tmp_tezina!=0)
                        res.push_back(tmp_tezina);
                    for(auto&[sused,tezina]:susedi[tmp]){
                        if(!mst[sused] && tezina < rastojanja[sused]){
                            rastojanja[sused] =tezina;
                            pq.push({rastojanja[sused],sused});
                        }
                    }
                }
            }
        }
        sort(res.begin(),res.end(),greater<int>());
        for(auto x : res)
            cout << x << ' ';
        cout << endl;
        return res[k-2];
    }
};

int main(){

    ios_base::sync_with_stdio(false);
   
    int k,n,p;
    cin >> k>> n>>p;
    Graph *G = new Graph(n);
    for(int i=0; i<p; i++){
        int u,v,w;
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }
    cout << G->primov(k) << endl;
    return 0;
}