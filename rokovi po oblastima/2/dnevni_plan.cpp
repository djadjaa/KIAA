#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> inDeg;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        inDeg.resize(V,0);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        inDeg[v]++;
    }

    int topolosko(){
        queue<int> q;
        int res=0;

        for(int i=0; i<V; i++){
            if(inDeg[i]==0)
                q.push(i);
        }
        if(q.empty())
            return -1;
        q.push(-1);

        while(!q.empty()){
            int tmp = q.front();
            q.pop();

            if(tmp==-1){
                res++;
                if(q.empty())
                    break;
                q.push(-1);
                continue;
            }

            for(auto sused : susedi[tmp]){
                inDeg[sused]--;
                if(inDeg[sused]==0)
                    q.push(sused);
            }
        }
        
        for(int i=0; i<V; i++){
            if(inDeg[i]>0)
                return -1;
        }

        return res;
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
    cout << G->topolosko() << endl;
    return 0;
}