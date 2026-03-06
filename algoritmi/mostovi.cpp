#include <bits/stdc++.h>

using namespace std;

int discoveryTime=0;
vector<pair<int,int>> mostovi;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> times;
    vector<int> lowlink;
    vector<int> roditelj;
    vector<bool> posecen;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        times.resize(V,-1);
        lowlink.resize(V,-1);
        roditelj.resize(V,-1);
        posecen.resize(V,false);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void Tarjan(int cvor){
        posecen[cvor] = true;
        times[cvor] = discoveryTime++;
        lowlink[cvor] = times[cvor];
        
        //cout << "cvor: " << cvor << " disc time: " << times[cvor] << endl;
        for(auto sused : susedi[cvor]){
            if(posecen[sused]){
                if(sused!=roditelj[cvor])
                    lowlink[cvor] = min(lowlink[cvor],times[sused]);
            }else{
                roditelj[sused] = cvor;
                Tarjan(sused);

                lowlink[cvor] = min(lowlink[sused],lowlink[cvor]);

                if(lowlink[sused]>times[cvor])
                    mostovi.push_back({cvor,sused});
            }   
        }
    }

    void ispisi(){
        Tarjan(0);
        if(mostovi.size()>0)
            cout << 0 << endl;
        else{
            for(int i=0; i<V; i++){
                for(auto sused : susedi[i]){
                    if(i>sused)
                        continue;
                    if(times[i]>times[sused])
                        swap(i,sused);
                    if(roditelj[sused] = i)
                        cout << i+1 << ' ' << sused+1 << endl;
                    else
                        cout << sused+1 << ' ' << i+1 << endl;
                }
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
        G->dodajGranu(u-1,v-1);
    }

    G->ispisi();
    return 0;
}