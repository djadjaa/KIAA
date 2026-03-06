#include <bits/stdc++.h>

using namespace std;

struct Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,-w});
    }

    void dfs(int visinaTla){
        vector<int> posecen(V, false);
        vector<int> visine(V,INT_MAX);

        stack<int> s;

        visine[0]=visinaTla;
        s.push(0);
        posecen[0]=true;

        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            for(auto &[sused,susedvisina]:susedi[tmp]){
                if(!posecen[sused]){
                    visine[sused] = visine[tmp]+susedvisina;
                    s.push(sused);
                    posecen[sused] = true;
                }
            }
        }
        cout << *min_element(visine.begin(), visine.end()) << endl;
    }
};

int main(){

    int visinaTla, n, m;
    cin >> visinaTla >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v,visina;
        cin >> u >> v >> visina;
        G->dodajGranu(u,v,visina);
    }

    G->dfs(visinaTla);
    return 0;
}