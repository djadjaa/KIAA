#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int dest;
    int brKuca;
    bool posecenaGrana;
};

class Graph{
    private:
    int V;
    vector<vector<Edge>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, int c, bool ind){
        susedi[u].push_back({v,c,ind});
        susedi[v].push_back({u,c,ind});
    }

    void dfs(int start,int k){
        long long zarada = 0;
        stack<int> s;
        vector<int> put;

        s.push(start);

        while(!s.empty()){
            int tmp = s.top();
            //uklanjamo cvor sa steka akko je grana posecena zato necemo raditi s.pop()
            bool pronadjen = false;

            for(auto &g : susedi[tmp]){
                if(!g.posecenaGrana){
                    g.posecenaGrana = true;
                    //idemo na granu susednu od tekuce
                    for(auto &h : susedi[g.dest]){
                        if(h.dest == tmp && !h.posecenaGrana){
                            h.posecenaGrana = true;
                            break;
                        }
                    }
                    zarada += 1LL*g.brKuca*k;
                    s.push(g.dest); //ubacujemo suseda
                    pronadjen = true;
                    break;
                }
            }

            if(!pronadjen){
                //ako smo obisli celu granu
                s.pop();
                put.push_back(tmp);
            }
        }
        for(int x : put)
            cout << x << ' ';
        cout << endl << zarada << endl;
    }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin >> n >> m >> k;
    Graph *G = new Graph(n+1);
    for(int i=0; i<m; i++){
        int u,v,c;
        cin >> u >> v >> c;
        G->dodajGranu(u,v,c,false);
    }
    int start;
    cin >> start;
    G->dfs(start,k);
    return 0;
}