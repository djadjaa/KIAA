#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool>posecen;
    vector<int> dfsDrvo;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
    }

    void dfs(int u){
        stack<int> s;
        s.push(u);
        posecen[u] = true;
        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            dfsDrvo.push_back(tmp);

            for(int sused : susedi[tmp]){
                if(posecen[sused])
                    continue;
                posecen[sused] = true;
                s.push(sused);
            }
        }
        for(auto x : dfsDrvo)
            cout << x << ' ';
        cout << endl;
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
    G->dfs(0);

    return 0;
}