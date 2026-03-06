#include <bits/stdc++.h>

using namespace std;

struct Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void dfs(int root){
        vector<pair<int,int>> edges;
        edges.reserve(V-1);
        vector<bool> posecen(V,false);

        stack<int> s;
        s.push(root);
        posecen[root]=true;

        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            for(int sused : susedi[tmp]){
                if(!posecen[sused]){
                    s.push(sused);
                    posecen[sused] = true;
                    edges.emplace_back(tmp,sused);
                }
            }
        }
        sort(begin(edges),end(edges));
        for(const auto &p : edges)
            cout << p.first << ' ' << p.second << endl;
    }
};

int main(){

    int n;
    cin >> n;
    Graph *G = new Graph(n);
    for(int i=0; i<n-1; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    int root;
    cin >> root;
    G->dfs(root);
    delete G;
    return 0;
}