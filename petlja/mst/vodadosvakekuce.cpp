#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>>susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V+1);
    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int primov(){
        priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>>pq;
        vector <int> rastojanja(V+1,numeric_limits<int>::max());
        vector<bool> mst(V+1,false);
        int res=0;
        for(int start = 0; start<V; start++){
            if(!mst[start]){
                rastojanja[start]=0;
                pq.push({rastojanja[start],start});
                while(!pq.empty()){
                    int tmp = pq.top().second;
                    pq.pop();
                    if(mst[tmp])
                        continue;
                    mst[tmp] = true;
                    res += rastojanja[tmp];
                    for(auto &[sused,tezina]:susedi[tmp]){
                        if(!mst[sused] && tezina<rastojanja[sused]){
                            rastojanja[sused] = tezina;
                            pq.push({rastojanja[sused],sused});
                        }
                    }
                }
            }
        }
        return res;
    }

};

int main(){


    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    Graph *G = new Graph(n+1);
    for(int i=1; i<=n; i++){
        int cena;
        cin >> cena;
        /*
        0 ce nam predstavljati bunar odakle ce kuca
        biti snadbevana vodom
        i nam je kuca
        */
        G->dodajGranu(0,i,cena);
    }
    int u,v,w;
    while(cin >>u>>v>>w){
        //sa druge strane gran u->v nam je cev od kuce do kuce
        G->dodajGranu(u,v,w);
    }
    cout << G->primov() << endl;


    return 0;
}