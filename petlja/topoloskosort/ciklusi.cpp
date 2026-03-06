#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> inDeg;
    //vector<int> res;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        inDeg.resize(V,0);
        //res.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[v].push_back(u);
        inDeg[u]++;
    }

    bool Kanov(){
        queue<int> nodes;
        for(int i=0; i<V; i++){
            if(inDeg[i]==0)
                nodes.push(i);
        }
        int tmp;
        int brObradjenih=0;
        while(!nodes.empty()){
            tmp = nodes.front();
            nodes.pop();
            brObradjenih++;
            for(int sused : susedi[tmp]){
                inDeg[sused]--;
                if(inDeg[sused]==0)
                    nodes.push(sused);
            }
        }
        if(brObradjenih!=V)
            return true;
        else
            return false;
    }
};

int main() {
    int n;
    cin >> n;
    while(n--){
        int v,e;
        cin >> v >> e;
        Graph *G = new Graph(v);
        for(int i=0; i<e; i++){
            int u,v;
            cin >> u >> v;
            G->dodajGranu(u,v);
        }
        if(G->Kanov())
            cout << "da\n";
        else
            cout << "ne\n";
    }
    return 0;
}