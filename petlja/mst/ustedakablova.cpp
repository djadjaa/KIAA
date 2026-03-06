#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,double>>>susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, double w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    double primov(){
        priority_queue<pair<int,double>, vector<pair<int,double>>, greater<pair<int,double>>> pq;
        vector<double> key(V,INFINITY); //najmanje rastojanje svakog cvora od trenutnog stabla
        vector<bool> MST(V, false);
        double ukTezina=0;

        for(int start =0 ; start <V; start++){
            if(!MST[start]){
                pq.push({start,0});
                key[start] = 0;

                while(!pq.empty()){
                    int tmp = pq.top().first;
                    pq.pop();
                    if(MST[tmp])
                        continue;
                    MST[tmp] = true;
                    ukTezina += key[tmp];

                    for(auto &[sused,tezina]:susedi[tmp]){
                        if(!MST[sused] && key[sused] > tezina){
                            key[sused] = tezina;
                            pq.push({sused,key[sused]});
                        }
                    }
                }
            }
        }
        return ukTezina;
    }

};

int main(){


    ios_base::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        double w;
        cin >>u>>v>>w;
        G->dodajGranu(u,v,w);
    }
    cout << fixed << showpoint << setprecision(1) << G->primov() << endl;


    return 0;
}