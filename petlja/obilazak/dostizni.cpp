#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u,int v){
        susedi[u].push_back(v);
    }

    void dfs(int start, int end){
        vector<bool> posecen(V,false);
        stack<int>q;
        q.push(start);
        posecen[start] = true;
        bool povezan = false;
        while(!q.empty() && !povezan){
            int tmp = q.top();
            q.pop();

            for(int sused : susedi[tmp]){
                if(sused == end){
                    povezan = true;
                    break;
                }
                if(!posecen[sused]){
                    posecen[sused]= true;
                    q.push(sused);
                }
            }
        }
        if(povezan)
            cout << "da\n";
        else
            cout << "ne\n";
    }
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        u--;
        v--;
        G->dodajGranu(u,v);
    }
    int q;
    cin >> q;
    while(q--){
        int start,end;
        cin >> start >> end;
        start--;
        end--;
        G->dfs(start,end);
    }
    return 0;
}