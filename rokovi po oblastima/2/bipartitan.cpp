#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> boje;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        boje.resize(V,-1);
    }

    void dodajGranu(int u,int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    bool bipartitan(int cvor){
        stack<int> s;
        s.push(cvor);
        boje[cvor]=0;
        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            for(int sused : susedi[tmp]){
                if(boje[sused]==-1){
                    boje[sused] = 1-boje[tmp];
                    s.push(sused);
                }
                else if(boje[sused]==boje[tmp])
                    return false;
            }
        }
        return true;
    }

    void query(){
        for(int i=0; i<V; i++){
            if(boje[i]==-1){
                if(!bipartitan(i)){
                    cout << "-\n";
                    return;
                }
            }
        }
        for(int i=0; i<V; i++){
            if(boje[i]==0)
                cout << i << ' ';
            cout << endl;
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
        G->dodajGranu(u,v);
    }
    G->query();

    return 0;
}