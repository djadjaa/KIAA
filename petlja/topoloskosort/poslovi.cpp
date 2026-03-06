#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>>susedi;
    vector<int> inDeg;
    //vector<int> res;

    public:
    Graph(int V){
        this->V = V;
        inDeg.resize(V,0);
        susedi.resize(V);
        //res.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[v].push_back(u);
        inDeg[u]++;
    }

    void Kanov(){
        queue<int> nodes;
        for(int i=0; i<V; i++){
            if(inDeg[i]==0)
                nodes.push(i);
        }
        int tmp;
        while(!nodes.empty()){
            tmp = nodes.front();
            cout << tmp << endl;
            nodes.pop();

            //res.push_back(tmp);

            for(int sused : susedi[tmp]){
                inDeg[sused]--;
                if(inDeg[sused]==0)
                    nodes.push(sused);
            }
        }
        /*
        for(auto x : res)
            cout << x << endl;*/
    }
};

int main(){

    int n,m;
    cin >> n >> m;

    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    G->Kanov();

    return 0;
}