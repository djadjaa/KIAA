#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>>susedi;
    vector<int> boje;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        boje.resize(V,-1);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    bool bipartitan(int cvor){
        boje[cvor] = 0;
        stack<int> s;
        s.push(cvor);
        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            for(int sused : susedi[tmp]){
                if(boje[sused]==-1){
                    boje[sused] = 1-boje[tmp];
                    s.push(sused);
                }
                
                if(boje[sused]!=-1 && boje[sused]==boje[tmp])
                    return false;
            }
        }
        return true;
    }

    void ispisi(){
        for(int i=0; i<V; i++){
            if(boje[i]==-1){
                if(!bipartitan(i)){
                    cout << "-";
                    return;
                }
            }
        }
        for(int i=0; i<V; i++){
            if(boje[0]==boje[i])
                cout << i << ' ';
        }
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
    G->ispisi();

    return 0;
}