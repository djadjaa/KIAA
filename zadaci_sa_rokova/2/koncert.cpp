#include <bits/stdc++.h>

using namespace std;

vector<int> atmosfere;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> roditelj;
    vector<int> lowlink;
    vector<int> times;
    vector<bool> posecen;
    vector<bool> artikulacioneTacke;
    int discoveryTime;

    public:
    Graph(int V){
        this->V = V;
        discoveryTime = 0;
        susedi.resize(V);
        lowlink.resize(V,-1);
        times.resize(V,-1);
        artikulacioneTacke.resize(V,false);
        posecen.resize(V,false);
        roditelj.resize(V,-1);

    }

    void addEdges(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void Tarjan(int cvor){
        int numChilds=0;
        times[cvor] = discoveryTime++;
        posecen[cvor] = true;
        lowlink[cvor] = times[cvor];

        for(auto sused : susedi[cvor]){
            if(posecen[sused]){
                if(roditelj[cvor]!=sused)
                    lowlink[cvor] = min(lowlink[cvor],times[sused]);
            }else{
                numChilds++;
                roditelj[sused] = cvor;

                Tarjan(sused);
                lowlink[cvor] = min(lowlink[sused],lowlink[cvor]);

                if(roditelj[cvor]!=-1 && lowlink[sused]>=times[cvor])
                    artikulacioneTacke[cvor] = true;
            }
        }

        if(roditelj[cvor]==-1 && numChilds>1)
            artikulacioneTacke[cvor] =true;
    }

    void res(){
        Tarjan(0);
        int sum=0;
        for(int i=0; i<artikulacioneTacke.size(); i++){
            if(artikulacioneTacke[i]){
                cout << i << endl;
                sum += atmosfere[i];
            }
        }
        if(sum<=0)
            cout << "NEGATIVNA ";
        else
            cout << "POZITIVNA ";
        cout << sum << endl;
    }
};

int main(){

    int n,m;
    cin >> n >> m;
    atmosfere.resize(n);
    for(int i=0; i<n; i++)
        cin >> atmosfere[i];
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->addEdges(u,v);
    }
    G->res();

    return 0;
}